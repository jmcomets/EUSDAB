#include <input/controller.h>

namespace EUSDAB
{
    namespace Input
    {
        Controller::Controller():
            _playerList(),
            _allSpeakers(),
            _keyMapping()
        {
        }

        // TODO make this code cleaner
        void Controller::initMappings()
        {
            _keyMapping[sf::Keyboard::Z] = std::make_pair(_playerList[0], Event::Up);
            _keyMapping[sf::Keyboard::S] = std::make_pair(_playerList[0], Event::Down);
            _keyMapping[sf::Keyboard::Q] = std::make_pair(_playerList[0], Event::Left);
            _keyMapping[sf::Keyboard::D] = std::make_pair(_playerList[0], Event::Right);

            _keyMapping[sf::Keyboard::Up] = std::make_pair(_playerList[1], Event::Up);
            _keyMapping[sf::Keyboard::Down] = std::make_pair(_playerList[1], Event::Down);
            _keyMapping[sf::Keyboard::Left] = std::make_pair(_playerList[1], Event::Left);
            _keyMapping[sf::Keyboard::Right] = std::make_pair(_playerList[1], Event::Right);
        }

        void Controller::update()
        {
            // Handle continuous input
            for (auto p : _keyMapping)
            {
                if (sf::Keyboard::isKeyPressed(p.first))
                {
                    Event event(p.second.second, Event::Full, Event::ContinuousEdge);
                    p.second.first->push(event);
                }
            }

            // TODO Joystick

            for (Speaker * s : _allSpeakers)
            {
                s->pollEvents();
            }
        }

        void Controller::addSpeaker(Speaker * s)
        {
            _allSpeakers.insert(s);
        }

        void Controller::pushEvent(const sf::Event & event)
        {
            if (event.type == sf::Event::KeyPressed)
            {
                auto it = _keyMapping.find(event.key.code);
                if (it != _keyMapping.end())
                {
                    Event event(it->second.second, Event::Full, Event::RisingEdge);
                    it->second.first->push(event);
                }
            }
            if (event.type == sf::Event::KeyReleased)
            {
                auto it = _keyMapping.find(event.key.code);
                if (it != _keyMapping.end())
                {
                    Event event(it->second.second, Event::Full, Event::FallingEdge);
                    it->second.first->push(event);
                }
            }

            // TODO Joystick : rising and falling edge
        }

        void Controller::pushEvent(Speaker * s, Event const & event)
        {
            addSpeaker(s);
            s->push(event);
        }

        void Controller::nextFrame()
        {
            Event event(Event::NextFrame, Event::Full, Event::RisingEdge);
            for (Speaker * s : _allSpeakers)
            {
                s->push(event);
            }
        }
    }
}

