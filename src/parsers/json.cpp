#include <parsers/json.h>
#include <istream>
#include <utility>
#include <stdexcept>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <states/idle.h>
#include <states/test.h>

using namespace boost::property_tree;

namespace EUSDAB
{
    namespace Parsers
    {
        // Make code more readable
        //using namespace Input;
        typedef Entity::Hitbox Hitbox;

        Json::~Json()
        {
        }

        // Internal utility function for reading an Entity's 
        //   State JSON representation.
        static std::pair<Movement, State *> readState(const ptree & statePt);

        // Internal utility function for reading an Entity's
        //   Movement JSON representation.
        static Movement readMovement(const ptree & mvtPt);

        Entity * Json::readEntity(std::istream & is) const
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
            std::string name = entityPt.get<std::string>("name");
            entity->setName(name);

            // Entity's states
            ptree stateNodes = entityPt.get_child("states");
            try
            {
                for (auto s : stateNodes)
                {
                    std::pair<Movement, State *> stateInfo = readState(s.second);
                    entity->addState(stateInfo.first, stateInfo.second);
                }
                entity->setState(Movement(Movement::Idle | Movement::Left)); // FIXME
            }
            catch (ptree_error e)
            {
                delete entity;
                entity = nullptr;
            }
            return entity;
        }

        Hitbox * readHitbox(std::istream & is)
        {
            // Boost's magic
            ptree hbPt;
            try
            {
                read_json(is, hbPt);
            }
            catch (ptree_error)
            {
                std::cerr << "Hitbox JSON file invalid" << std::endl;
                return nullptr;
            }

            // Hitbox to construct
            Hitbox * hb = new Hitbox();

            // Hitbox's AABBs
            ptree aabbNodes = hbPt.get_child("aabbs");
            try
            {
                for (auto aabb : aabbNodes)
                {
                    // TODO
                }
            }
            catch (ptree_error)
            {
                delete hb;
                hb = nullptr;
            }
            return hb;
        }

        std::pair<Movement, State *> readState(const ptree & statePt)
        {
            // State to be constructed
            State * state = nullptr;

            try
            {
                // FIXME handle "type" field and specific states
                state = new States::Idle();

                // Parse movement
                Movement mvt = readMovement(statePt.get_child("movement"));

                // Parse hitbox file
                Hitbox * hb = nullptr;
                std::string hbFilename = statePt.get<std::string>("hitbox");
                std::ifstream hbFile(hbFilename.c_str());
                if (hbFile.good())
                {
                    hb = readHitbox(hbFile);
                }
                //state->setHitbox(hb);

                // TODO parse tileset
                std::string tsFilename = statePt.get<std::string>("view.tileset");

                // TODO parse audio
                std::string audioFilename = statePt.get<std::string>("view.audio");

                return std::make_pair(mvt, state);
            }
            catch (ptree_error)
            {
                delete state;
                throw;
            }
        }

        Movement readMovement(const ptree & mvtPt)
        {
            Movement movement;
            ptree actions = mvtPt.get_child("action");
            Movement::Flag flag = 0;
            for (auto p : actions)
            {
                std::string action = p.second.data();
                if (action == "idle")
                {
                    flag |= Movement::Idle;
                }
                else if (action == "jump")
                {
                    flag |= Movement::Jump;
                }
                else if (action == "attack")
                {
                    flag |= Movement::Attack;
                }
                else if (action == "smash")
                {
                    flag |= Movement::Smash;
                }
                else if (action == "flee")
                {
                    flag |= Movement::Flee;
                }
                else if (action == "guard")
                {
                    flag |= Movement::Guard;
                }
                else if (action == "onhit")
                {
                    flag |= Movement::OnHit;
                }
                else
                {
                    throw std::runtime_error("Unrecognized movement");
                }
            }
            ptree directions = mvtPt.get_child("direction");
            for (auto p : directions)
            {
                std::string direction = p.second.data();
                if (direction == "up")
                {
                    flag |= Movement::Up;
                }
                else if (direction == "down")
                {
                    flag |= Movement::Down;
                }
                else if (direction == "left")
                {
                    flag |= Movement::Left;
                }
                else if (direction == "right")
                {
                    flag |= Movement::Right;
                }
                else
                {
                    throw std::runtime_error("Unrecognized direction");
                }
            }
            movement.setFlag(flag);
            std::cout << "flag parsed: " << flag << std::endl;
            return movement;
        }
    }
}
