#include <input/controller.h>

namespace EUSDAB
{
    namespace Input
    {
        Controller::Controller(std::array<Entity *, Config::NbPlayers> players):
            _playerList(), _entityList(),
            _keyMapping()
        {
            // Remplissage de players (et de ta mère JM)
            // TODO

            // Mapping des touches claviers
            // TODO
            _keyMapping[sf::Keyboard::Z] = std::make_pair();
        }

        void Controller::update()
        {
            for (Speaker * s : _speakers)
            {
                s->pollEvents();
            }
        }

        void Controller::addSpeaker(Speaker * s)
        {
            _speakerList.push_back(s);
        }

        void Controller::addEntity(const Entity &)
        {
            // TODO
        }

        const Event & Controller::translate(const sf::Event & e)
        {
            if (e.type == sf::Event::KeyPressed)
            {
                if ( (auto it = _keyMapping.find(e.key.code)) != _keyMapping.end() )
                {
                    Event event(it-second.second, Event::Full, Event::RisingEdge);
                    it->second.first->push(event);
                }
            }
            else if (e.type == sf::Event::KeyReleased)
            {
                if ( (auto it = _keyMapping.find(e.key.code)) != _keyMapping.end() )
                {
                    Event event(it-second.second, Event::Full, Event::FallingEdge);
                    it->second.first->push(event);
                }
            }

            // TODO Joystick

            throw std::runtime_error("Event not recognized");
        }
    }
}

