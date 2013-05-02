#include <entityparser.h>
#include <istream>
#include <stdexcept>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <entitywithmask.h>
#include <states/all.h>

using namespace boost::property_tree;

namespace EUSDAB
{
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
    //  - is is a "good" std::istream
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
        Entity * entity = nullptr;

        // Entity polymorphism
        try
        {
            const std::string & entityId = entityPt.get<std::string>("entityId");
            if (entityId == "withmask")
            {
                entity = new EntityWithMask();
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
                    // TODO finish
                    const std::string & stateId = statePt.get<std::string>("type");
                    {
                        using namespace States;
                        if (stateId == "idle") { state = new States::Idle(); }
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
                    const std::string & animName = statePt.get<std::string>("animation");
                    Animation * animation = _animParser.loadAnimation(entityDir + "/animations/" + animName);
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
}
