#include <parsers/json.h>
#include <istream>
#include <utility>
#include <stdexcept>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <input/states/idle.h>
#include <input/states/test.h>

using namespace boost::property_tree;

namespace EUSDAB
{
    namespace Parsers
    {
        Json::~Json()
        {
        }

        // Internal utility function for reading an Entity's 
        //   Input::State JSON representation.
        static std::pair<Movement, Input::State *> readState(const ptree & statePt);

        // Internal utility function for reading an Entity's
        //   Movement JSON representation.
        static Movement readMovement(const ptree & mvtPt);

        Entity * Json::read(std::istream & is) const
        {
            // Boost's magic
            ptree entityPt;
            read_json(is, entityPt);

            // Entity to construct
            Entity * entity = new Entity();

            // Entity's name
            std::string name = entityPt.get<std::string>("name");
            std::cout << "name : " << name << std::endl;
            entity->setName(name);

            // Entity's states
            ptree stateNodes = entityPt.get_child("states");
            try
            {
                for (auto s : stateNodes)
                {
                    std::pair<Movement, Input::State *> stateInfo = readState(s.second);
                    entity->addState(stateInfo.first, stateInfo.second);
                }
            }
            catch (ptree_error e)
            {
                delete entity;
                entity = nullptr;
            }
            return entity;
        }

        std::pair<Movement, Input::State *> readState(const ptree & statePt)
        {
            // State to be constructed
            Input::State * state = nullptr;

            try
            {
                // FIXME
                state = new Input::States::Idle();

                Movement mvt = readMovement(statePt.get_child("movement"));

                std::string hbFilename = statePt.get<std::string>("physics");
                std::cout << "hitbox : " << hbFilename << std::endl;

                std::string tsFilename = statePt.get<std::string>("view.tileset");
                std::cout << "tileset : " << tsFilename << std::endl;

                std::string audioFilename = statePt.get<std::string>("view.audio");
                std::cout << "audio : " << audioFilename << std::endl;

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
