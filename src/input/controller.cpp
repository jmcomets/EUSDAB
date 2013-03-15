#include <input/controller.h>

namespace EUSDAB
{
    namespace Input
    {
        Controller::Controller(std::array<Entity *, ::NBR_PLAYER> players):
            _player(),
            _entityList(),
            _key_map()
        {
            // Remplissage de _players
            
            // Mapping des touches claviers
            _key_map[sf::Keyboard::Z] = std::make_pair();
        }

        Controller::~Controller()
        {
        }

        void Controller::addEntity(::Entity const &)
        {
            //TODO
        }

        Event const & Controller::sfml2eusdab(sf::Event const & e)
        {
            if(e.type == sf::Event::KeyPressed)
            {
                if((auto it = _key_map.find(e.key.code)) != _key_map.end())
                {
                    Event event(it-second.second, Event::Full, Event::RisingEdge);
                    it->second.first->push(event);
                }
            }
            else if(e.type == sf::Event::KeyReleased)
            {
                if((auto it = _key_map.find(e.key.code)) != _key_map.end())
                {
                    Event event(it-second.second, Event::Full, Event::FallingEdge);
                    it->second.first->push(event);
                }
            }

            //TODO: Finir

            throw std::runtime_error("Event not recognized");
        }
    }
}

