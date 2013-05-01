#include <entityparser.h>
#include <memory>
#include <array>
#include <istream>
#include <utility>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <textureManager.h>
#include <states/all.h>

using boost::lexical_cast;
using namespace boost::property_tree;

namespace EUSDAB
{
    // Shortcuts
    typedef Physics::Unit Unit;
    typedef Physics::AABB<Unit> AABB;
    typedef Physics::Hitbox<Unit> Hitbox;

    // Concepts:
    //  - entityDir is a valid path to the Entity's directory,
    //      and contains no trailing slashes
    Entity * EntityParser::loadEntity(const std::string & entityDir) const
    {
        Entity * entity = nullptr;
        std::string entityFilename(entityDir + "/entity.json");
        std::ifstream entityFile(entityFilename.c_str());
        if (entityFile.good())
        {
            entity = readEntity(entityFile, entityDir);
        }
        return entity;
    }

    // Concepts:
    //  - is is a "good" std::istream, 
    //  - entityDir is a valid path to the Entity's directory,
    //      and contains no trailing slashes
    Entity * EntityParser::readEntity(std::istream & is,
            const std::string & entityDir) const
    {
        // Boost's magic
        ptree entityPt;
        try
        {
            read_json(is, entityPt);
        }
        catch (ptree_error)
        {
            std::cerr << "Entity JSON file invalid" << std::endl;
            return nullptr;
        }

        // Entity to construct
        Entity * entity = new Entity();

        // Entity's name
        const std::string & name = entityPt.get<std::string>("name");
        entity->setName(name);

        // Entity's start state
        const std::string & entityStartStateId = entityPt.get<std::string>("start");

        // Entity's states
        const ptree & stateNodes = entityPt.get_child("states");
        try
        {
            for (auto s : stateNodes)
            {
                // State ptree
                const ptree & statePt = s.second;

                // State
                State * state = nullptr;

                try
                {
                    // Underlying state
                    const std::string & stateId = statePt.get<std::string>("type");
                    state = new States::Idle(); // FIXME

                    // Movement
                    const ptree & mvtPt = statePt.get_child("movement");
                    const ptree & actions = mvtPt.get_child("action");
                    Movement::Flag flag = 0;
                    for (auto p : actions)
                    {
                        const std::string & action = p.second.data();
                        if (action == "idle") { flag |= Movement::Idle; }
                        else if (action == "jump") { flag |= Movement::Jump; }
                        else if (action == "attack") { flag |= Movement::Attack; }
                        else if (action == "smash") { flag |= Movement::Smash; }
                        else if (action == "flee") { flag |= Movement::Flee; }
                        else if (action == "guard") { flag |= Movement::Guard; }
                        else if (action == "onhit") { flag |= Movement::OnHit; }
                        else { throw std::runtime_error("Unrecognized action"); }
                    }
                    const ptree & directions = mvtPt.get_child("direction");
                    for (auto p : directions)
                    {
                        const std::string & direction = p.second.data();
                        if (direction == "up") { flag |= Movement::Up; }
                        else if (direction == "down") { flag |= Movement::Down; }
                        else if (direction == "left") { flag |= Movement::Left; }
                        else if (direction == "right") { flag |= Movement::Right; }
                        else { throw std::runtime_error("Unrecognized direction"); }
                    }
                    state->setMovement(Movement(flag));

                    // Animation file (physics/hitbox)
                    Animation * animation = nullptr;
                    const std::string & animFilename = statePt.get<std::string>("animation");
                    std::ifstream animFile(animFilename.c_str());
                    if (animFile.good())
                    {
                        animation = readAnimation(animFile, entityDir);
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
        catch (ptree_error e)
        {
            delete entity;
            entity = nullptr;
        }
        catch (std::runtime_error)
        {
            delete entity;
            entity = nullptr;
        }
        return entity;
    }

    // Concepts:
    //  - is is a "good" std::istream, 
    //  - entityDir is a valid path to the Entity's directory,
    //      and contains no trailing slashes
    Animation * EntityParser::readAnimation(std::istream & is,
            const std::string & entityDir) const
    {
        // Boost's magic
        ptree animationPt;
        try
        {
            read_json(is, animationPt);
        }
        catch (ptree_error)
        {
            std::cerr << "Animation JSON file invalid" << std::endl;
            return nullptr;
        }

        // Actual animation parsing
        std::string animationDir(entityDir + "/animations");
        Animation * animation = new Animation();
        try
        {
            for (auto a : animationPt)
            {
                // Animation is dict frame filename -> frame,
                //  where the filename is relative to the
                //  Entity's "animations" directory
                std::string frameImagePath(animationDir + "/" + a.first);
                const ptree & hitboxesPt = a.second;

                // Load texture
                typedef Graphics::TextureManager TextureManager;
                typedef TextureManager::TexturePtr TexturePtr;
                TexturePtr tx = TextureManager::loadTexture(frameImagePath);

                // Parse Hitboxes
                // List of different hitboxes
                std::array<Hitbox, 5> frameHitboxes = {
                    Hitbox(Hitbox::Defense),
                    Hitbox(Hitbox::Attack),
                    Hitbox(Hitbox::Grabable),
                    Hitbox(Hitbox::Grab),
                    Hitbox(Hitbox::Foot),
                };

                // Parse all AABBs
                for (auto p : hitboxesPt)
                {
                    const ptree & hb = p.second;
                    Unit x = lexical_cast<Unit>(hb.get<std::string>("center.x"));
                    Unit y = lexical_cast<Unit>(hb.get<std::string>("center.y"));
                    Unit width = lexical_cast<Unit>(hb.get<std::string>("width"));
                    Unit height = lexical_cast<Unit>(hb.get<std::string>("height"));

                    // Hitbox semantic
                    Hitbox::Semantic sem;
                    const std::string & semantic = hb.get<std::string>("semantic");
                    if (semantic == "defense") { sem = Hitbox::Defense; }
                    else if (semantic == "foot") { sem = Hitbox::Foot; }
                    else if (semantic == "attack") { sem = Hitbox::Attack; }
                    else if (semantic == "grab") { sem = Hitbox::Grab; }
                    else if (semantic == "grabable") { sem = Hitbox::Grabable; }
                    else { throw std::runtime_error("Unknown hitbox semantic"); }

                    // Ensure Hitbox is in set and add AABB to it
                    AABB frameAABB = AABB(x, y, width, height);
                    Hitbox & frameHitbox = *std::find(frameHitboxes.begin(),
                            frameHitboxes.end(), Hitbox(sem));
                    frameHitbox.addAABB(frameAABB);
                }

                // Add finalized frame to animation
                animation->addFrame(Frame(tx.get(), frameHitboxes.begin(), 
                            frameHitboxes.end()));
            }
        }
        catch (ptree_error)
        {
            delete animation;
            animation = nullptr;
        }
        return animation;
    }
}
