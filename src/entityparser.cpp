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

using namespace boost::property_tree;

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
                            left += min_x * (max_y - min_y);
                            right += max_x * (max_y - min_y);
                            top += min_y * (max_x - min_x);
                            bottom += max_y * (max_x - min_x);
                            nbr_x += max_y - min_y;
                            nbr_y += max_x - min_x;
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
        catch (ptree_error)
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
                    TextureManager::TexturePtr tx = TextureManager::loadTexture(
                        Filename::join(_baseDirectory, entityDir, "backgrounds", txFile));
                    m->addAnimatedBackground(tx, parseVector2(bgPt.get_child("velocity")));
                }
                entity = m;
            }
            else
            {
                entity = new Entity();
            }
        }
        catch (ptree_error)
        {
            entity = new Entity();
        }

        // Entity's name
        const std::string & name = entityPt.get<std::string>("name");
        entity->setName(name);

        // Entity's start state
        const std::string & entityStartStateId = entityPt.get<std::string>("start");

        // Entity's own animation parser
        std::string animDir(Filename::join(_baseDirectory, entityDir, "animations"));
        AnimationParser & animParser = _animationParsers.insert(
                std::make_pair(animDir, AnimationParser(animDir))).first->second;

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
                    // Underlying state
                    // TODO finish
                    const std::string & stateId = statePt.get<std::string>("type");
                    {
                        if (stateId == "base")
                        {
                            state = new State();
                        }
                        else if (stateId == "idle" || stateId == "attack" || stateId == "onhit")
                        {
                            using Physics::Unit;
                            Unit slidingRatio = statePt.get<Unit>("sliding_ratio");
                            if (stateId == "idle")
                            {
                                States::Idle * idleState = new States::Idle();
                                idleState->setSlidingRatio(slidingRatio);
                                state = idleState;
                            }
                            else if (stateId == "onhit")
                            {
                                States::Hit * onhitState = new States::Hit();
                                state = onhitState;
                            }
                            else
                            {
                                States::Attack * attackState = new States::Attack();
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
                                States::Walk * walkState = new States::Walk();
                                walkState->setVelocity(velocity);
                                state = walkState;
                            }
                            else if (stateId == "jump")
                            {
                                States::Jump * jumpState = new States::Jump();
                                jumpState->setVelocity(velocity);
                                state = jumpState;
                            }
                            else if (stateId == "falling")
                            {
                                States::Falling * fallingState = new States::Falling();
                                fallingState->setVelocity(velocity);
                                state = fallingState;
                            }
                            else
                            {
                                States::Run * runState = new States::Run();
                                runState->setVelocity(velocity);
                                state = runState;
                            }
                        }
                        else if (stateId == "special") { state = new States::Special();}
                        else if(stateId == "aerial_attack") { state = new States::AerialAttack();}
                        else { throw std::runtime_error("Undefined state id"); }
                    }

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
                        else if (action == "guard") { flag |= Movement::Guard; }
                        else if (action == "onhit") { flag |= Movement::OnHit; }
                        else if (action == "falling") { flag |= Movement::Falling; }
                        else if (action == "special") { flag |= Movement::Special; }
                        else if (action == "aerial_attack") { flag |= Movement::AerialAttack; }
                        else { throw std::runtime_error("Unrecognized action"); }
                    }
                    const ptree & directions = mvtPt.get_child("direction");
                    int i = 0;
                    for (auto p : directions)
                    {
                        i++;
                        const std::string & direction = p.second.data();
                        if (direction == "up") { flag |= Movement::Up; }
                        else if (direction == "down") { flag |= Movement::Down; }
                        else if (direction == "left") { flag |= Movement::Left; }
                        else if (direction == "right") { flag |= Movement::Right; }
                        else { throw std::runtime_error("Unrecognized direction"); }
                        std::cout << "directions : " << i  << " | flag : " << flag << std::endl;
                    }
                    state->setMovement(Movement(flag));

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
                        catch (ptree_error)
                        {
                            delete attack;
                        }
                    }
                    catch (ptree_error)
                    {
                    }

                    // Animation file (physics/hitbox)
                    const std::string & animName = statePt.get<std::string>("animation");
                    Animation * animation = animParser.loadAnimation(animName);
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
                catch (ptree_error)
                {
                    delete state;
                    throw;
                }
                catch (std::runtime_error)
                {
                    delete state;
                    throw;
                }
            }
        }
        catch (ptree_error)
        {
            delete entity;
            entity = nullptr;
        }
        catch (std::runtime_error)
        {
            delete entity;
            entity = nullptr;
            throw;
        }
        return entity;
    }

    std::string EntityParser::baseDirectory() const
    {
        return _baseDirectory;
    }
}
