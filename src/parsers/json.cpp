#include <parsers/json.h>
#include <istream>
#include <utility>
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

        // Utility function for reading an Entity's 
        //   Input::State JSON representation.
        static std::pair<Movement, Input::State *> readState(const ptree & statePt);

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
                Movement mvt(Movement::Idle, Movement::Left);

                // FIXME
                state = new Input::States::Idle();

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
    }
}
