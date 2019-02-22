#include <entityparser.h>
#include <cassert>
#include <iostream>
#include <istream>
#include <stdexcept>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <states/all.h>
#include <util/filename.h>
#include <map.h>
#include <mutex>

using namespace boost::property_tree;

namespace {
    std::mutex s_animationLoaderMutex;
    std::mutex s_animationParserMutex;
    std::mutex s_soundLoaderMutex;
    std::mutex s_textureLoaderMutex;
}

namespace EUSDAB
{
    using namespace Util;

    EntityParser::EntityParser(const std::string & baseDirectory):
        _baseDirectory(Filename::clean(baseDirectory)), _animationParsers()
    {
    }

    // Concepts:
    //  - entityDir is a valid path to the Entity's directory,
    //      relative to base directory, and contains no trailing slashes
    Entity * EntityParser::loadEntity(const std::string & entityDir, bool ent_static)
    {
        Entity * entity = nullptr;
        std::string absEntityDir = Filename::join(_baseDirectory, entityDir, "entity.json");
        std::string entityFilename(absEntityDir);
        std::ifstream entityFile(entityFilename.c_str());
        if (entityFile.good())
        {
            entity = readEntity(entityFile, entityDir);
        }
        else
        {
            throw std::runtime_error("Wrong entity file " + absEntityDir);
        }

        assert(entity != nullptr);

        std::cout << ">>> Loading hitboxes of " << entity->name() << "..." << std::endl;

        // Calcul the global hitbox
        if(ent_static == false) {
            Physics::Unit left = 0;
            Physics::Unit right = 0;
            Physics::Unit top = 0;
            Physics::Unit bottom = 0;
            Physics::Unit nbr_x = 0;
            Physics::Unit nbr_y = 0;
            for(State * const & s : entity->states())
            {
                for(Frame & frame : s->animation()->frame_list())
                {
                    for(Physics::Hitbox const & hb : frame.hitboxList())
                    {
                        if(hb.semantic() & Physics::Hitbox::Defense
                                || hb.semantic() & Physics::Hitbox::Foot)
                        {
                            Physics::Unit min_x = 0, max_x = 1;
                            Physics::Unit min_y = 0, max_y = 1;
                            for(Physics::AABB const & aabb : hb.aabbList())
                            {
                                if(min_x > max_x)
                                {
                                    min_x = aabb.min().x;
                                    max_x = aabb.max().x;
                                }
                                if(min_y > max_y)
                                {
                                    min_y = aabb.min().y;
                                    max_y = aabb.max().y;
                                }
                                if(aabb.min().x < min_x)
                                    min_x = aabb.min().x;
                                if(aabb.min().y < min_y)
                                    min_y = aabb.min().y;
                                if(aabb.max().x > max_x)
                                    max_x = aabb.max().x;
                                if(aabb.max().y > max_y)
                                    max_y = aabb.max().y;
                            }

                            Physics::Unit factor_x = (max_x - min_x);
                            Physics::Unit factor_y = (max_y - min_y);
                            if(hb.semantic() & Physics::Hitbox::Foot)
                            {
                                factor_y *= static_cast<Physics::Unit>(8);
                            }
                            left += min_x * factor_x;
                            right += max_x * factor_x;
                            top += min_y * factor_y;
                            bottom += max_y * factor_y;
                            nbr_x += factor_x;
                            nbr_y += factor_y;
                        }
                    }
                }
            }
            Physics::Unit w = (right - left) / nbr_x;
            Physics::Unit h = (bottom - top) / nbr_y;
            Physics::Vector2 center(left / nbr_x + w / 2, top / nbr_y + h / 2);
            entity->hitbox().addAABB(Physics::AABB(center, w, h));
        }
        else
        {
            for(State * const & s : entity->states())
            {
                assert(s != nullptr);
                for(Frame & frame : s->animation()->frame_list())
                {
                    for(Physics::Hitbox const & hb : frame.hitboxList())
                    {
                        if(hb.semantic() & Physics::Hitbox::Defense)
                        {
                            Physics::Hitbox h(Physics::Hitbox::Collision);
                            for(Physics::AABB const & aabb : hb.aabbList())
                            {
                                h.addAABB(aabb);
                            }
                            frame.addHitbox(h);
                        }
                    }
                }
            }
        }

        return entity;
    }

    // Concepts:
    //  - is is a "good" std::istream
    //  - entityDir is a valid path to the Entity's directory,
    //      relative to base directory, and contains no trailing slashes
    Entity * EntityParser::readEntity(std::istream & is,
            const std::string & entityDir)
    {
        // Concept check
        assert(is.good());

        // Boost's magic
        ptree entityPt;
        try
        {
            read_json(is, entityPt);
        }
        catch (const ptree_error&)
        {
            std::cerr << "Entity " << entityDir << " JSON file invalid" << std::endl;
            return nullptr;
        }

        // Entity to construct
        Entity * entity = nullptr;

        // Helper for parsing Physics::Vector2
        static auto parseVector2 = [] (const ptree & pt)
        {
            using namespace Physics;
            return Vector2(pt.get<Unit>("x"), pt.get<Unit>("y"));
        };

        // Entity polymorphism
        try
        {
            const std::string & entityId = entityPt.get<std::string>("type");
            if (entityId == "map")
            {
                Map * m = new Map();
                const ptree & backgroundsPt = entityPt.get_child("backgrounds");
                for (auto bg : backgroundsPt)
                {
                    const ptree & bgPt = bg.second;
                    const std::string & txFile = bgPt.get<std::string>("texture");
                    using Graphics::TextureManager;

                    s_textureLoaderMutex.lock();

                    TextureManager::TexturePtr tx = TextureManager::loadTexture(
                        Filename::join(_baseDirectory, entityDir, "backgrounds", txFile));

                    s_textureLoaderMutex.unlock();

                    m->addAnimatedBackground(tx, parseVector2(bgPt.get_child("velocity")));
                }
                entity = m;
            }
            else
            {
                entity = new Entity();
            }
        }
        catch (const ptree_error&)
        {
            entity = new Entity();
        }

        // Entity's name
        const std::string & name = entityPt.get<std::string>("name");
        entity->setName(name);

        std::cout << ">> Loading entity: \"" << entity->name() << "\"" << std::endl;

        // Entity's start state
        const std::string & entityStartStateId = entityPt.get<std::string>("start");

        // Entity's own animation parser
        std::string animDir(Filename::join(_baseDirectory, entityDir, "animations"));

        s_animationParserMutex.lock();

        AnimationParser & animParser = _animationParsers.insert(
                std::make_pair(animDir, AnimationParser(animDir))).first->second;

        s_animationParserMutex.unlock();

        std::string soundDir(Filename::join(_baseDirectory, entityDir, "sounds"));


        std::cout << ">>> Loading states..." << std::endl;
        // Entity's states
        const ptree & statesPt = entityPt.get_child("states");
        try
        {
            for (auto s : statesPt)
            {
                // State ptree
                const ptree & statePt = s.second;

                // State
                State * state = nullptr;

                try
                {
                    // Movement
                    const ptree & mvtPt = statePt.get_child("movement");
                    const ptree & actions = mvtPt.get_child("action");
                    Movement::Flag flag = 0;
                    for (auto p : actions)
                    {
                        const std::string & action = p.second.data();
                        if (action == "idle") { flag |= Movement::Idle; }
                        else if (action == "walk") { flag |= Movement::Walk; }
                        else if (action == "run") { flag |= Movement::Run; }
                        else if (action == "jump") { flag |= Movement::Jump; }
                        else if (action == "attack") { flag |= Movement::Attack; }
                        else if (action == "smash") { flag |= Movement::Smash; }
                        else if (action == "flee") { flag |= Movement::Flee; }
                        else if (action == "dodge") { flag |= Movement::Dodge; }
                        else if (action == "guard") { flag |= Movement::Guard; }
                        else if (action == "crouch") { flag |= Movement::Crouch; }
                        else if (action == "stunned") { flag |= Movement::Stunned; }
                        else if (action == "shield_break") { flag |= Movement::ShieldBreak; }
                        else if (action == "stand") { flag |= Movement::Stand; }
                        else if (action == "shield") { flag |= Movement::Shield; }
                        else if (action == "onhit") { flag |= Movement::OnHit; }
                        else if (action == "falling") { flag |= Movement::Falling; }
                        else if (action == "special") { flag |= Movement::Special; }
                        else if (action == "aerial_attack") { flag |= Movement::AerialAttack; }
                        else { }//throw std::runtime_error("Unrecognized action"); }
                    }
                    const ptree & directions = mvtPt.get_child("direction");
                    for (auto p : directions)
                    {
                        const std::string & direction = p.second.data();
                        if (direction == "up") { flag |= Movement::Up; }
                        else if (direction == "down") { flag |= Movement::Down; }
                        else if (direction == "left") { flag |= Movement::Left; }
                        else if (direction == "right") { flag |= Movement::Right; }
                        else { }//throw std::runtime_error("Unrecognized direction"); }
                    }

                    Movement movement(flag);

                    // Underlying state
                    const std::string & stateId = statePt.get<std::string>("type");
                    {
                        if (stateId == "base")
                        {
                            state = new State(movement);
                        }
                        else if (stateId == "idle" || stateId == "attack" || stateId == "onhit")
                        {
                            using Physics::Unit;
                            Unit slidingRatio = statePt.get<Unit>("sliding_ratio");
                            if (stateId == "idle")
                            {
                                States::Idle * idleState = new States::Idle(movement);
                                idleState->setSlidingRatio(slidingRatio);
                                state = idleState;
                            }
                            else if (stateId == "onhit")
                            {
                                States::Hit * onhitState = new States::Hit(movement);
                                state = onhitState;
                            }
                            else
                            {
                                States::Attack * attackState = new States::Attack(movement);
                                attackState->setSlidingRatio(slidingRatio);
                                state = attackState;
                            }
                        }
                        else if (stateId == "walk" || stateId == "run"
                                || stateId == "jump" || stateId == "falling")
                        {
                            using namespace Physics;
                            Vector2 velocity = parseVector2(statePt.get_child("velocity"));
                            if (stateId == "walk")
                            {
                                States::Walk * walkState = new States::Walk(movement);
                                walkState->setVelocity(velocity);
                                state = walkState;
                            }
                            else if (stateId == "jump")
                            {
                                States::Jump * jumpState = new States::Jump(movement);
                                jumpState->setVelocity(velocity);
                                state = jumpState;
                            }
                            else if (stateId == "falling")
                            {
                                States::Falling * fallingState = new States::Falling(movement);
                                fallingState->setVelocity(velocity);
                                state = fallingState;
                            }
                            else
                            {
                                States::Run * runState = new States::Run(movement);
                                runState->setVelocity(velocity);
                                state = runState;
                            }
                        }
                        else if (stateId == "stand" || stateId == "stunned" || stateId == "shield_break")
                        {
                            Movement nextMovement(movement);
                            nextMovement.setAction(Movement::Idle);
                            state = new States::Wait(movement, nextMovement);
                        }

                        else if (stateId == "special") { state = new States::Special(movement);}
                        else if(stateId == "aerial_attack") { state = new States::AerialAttack(movement);}
                        else if(stateId == "guard") { state = new States::Guard(movement);}
                        else if(stateId == "shield") { state = new States::Shield(movement);}
                        else if(stateId == "crouch") { state = new States::Crouch(movement);}
                        else if(stateId == "aerial_dodge") { state = new States::AerialDodge(movement);}
                        else if(stateId == "dodge") { state = new States::Dodge(movement);}
                        else { }//throw std::runtime_error("Undefined state id"); }
                    }

                    // Attack
                    try
                    {
                        const ptree & attackPt = statePt.get_child("attack");
                        Attack * attack = new Attack();
                        try
                        {
                            attack->setDirection(attackPt.get<Physics::Unit>("direction.x"),
                                    attackPt.get<Physics::Unit>("direction.y"));
                            attack->setDamage(attackPt.get<Life::Amount>("damage"));
                            state->setAttack(attack);
                        }
                        catch (const ptree_error&)
                        {
                            delete attack;
                        }
                    }
                    catch (const ptree_error&)
                    {
                    }

                    const std::string & sound = statePt.get<std::string>("sound", "");

                    if(!sound.empty())
                        std::cout << ">>> Loading sound: " << entity->name() << "::" << sound << "..." << std::endl;

                    if(sound != "")
                    {
                        std::cout << "Adding sound : "
                            << Filename::join(soundDir, sound)
                            << std::endl;

                        s_soundLoaderMutex.lock();

                        Graphics::SoundManager::SoundPtr s = Graphics::SoundManager::loadSound(Filename::join(soundDir, sound));

                        s_soundLoaderMutex.unlock();

                        state->setSound(s);
                    }

                    //Animation file (physics/hitbox)
                    const std::string & animName = statePt.get<std::string>("animation");

                    if(!animName.empty())
                        std::cout << ">>> Loading animation: " << entity->name() << "::" << animName << "..." << std::endl;

                    s_animationLoaderMutex.lock();

                    Animation * animation = animParser.loadAnimation(animName);

                    s_animationLoaderMutex.unlock();

                    if (animation == nullptr)
                    {
                        throw std::runtime_error("`" + Filename::join("/",
                                    animParser.baseDirectory(), animName)
                                + "` Entity's animation wasn't loaded");
                    }
                    state->setAnimation(animation);

                    // Finalize state parsing
                    entity->addState(state);
                    if (entityStartStateId == stateId)
                    {
                        entity->setState(state);
                    }
                }
                catch (const ptree_error&)
                {
                    delete state;
                    throw;
                }
                catch (const std::runtime_error&)
                {
                    delete state;
                    throw;
                }
            }
        }
        catch (const ptree_error&)
        {
            delete entity;
            entity = nullptr;
        }
        catch (const std::runtime_error&)
        {
            delete entity;
            entity = nullptr;
            throw;
        }
        assert(entity != nullptr);
        return entity;
    }

    std::string EntityParser::baseDirectory() const
    {
        return _baseDirectory;
    }
}
