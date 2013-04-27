#include <input/controller.h>

namespace EUSDAB
{
    namespace Input
    {
        Controller::Controller():
            _allSpeakers(), _playerList(),
            _speakerList(), _keyMapping()
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

        Controller::~Controller()
        {
            for (auto pair : _allSpeakers)
            {
                delete pair.second;
            }
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

            for (Speaker * s : _playerList)
            {
                s->pollEvents();
            }

            for (Speaker * s : _speakerList)
            {
                s->pollEvents();
            }
        }

        void Controller::addEntity(Entity * e)
        {
            _speakerList.push_back(speaker(e));
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

        void Controller::pushEvent(Entity * e, Event const & event)
        {
            speaker(e)->push(event);
        }

        Speaker * Controller::speaker(Entity * e)
        {
            Speaker * s = nullptr;
            auto insertPair = _allSpeakers.insert(std::make_pair(e, s));
            if (insertPair.second)
            {
                insertPair.first->second = new Speaker(e->state());
            }
            return insertPair.first->second;
        }
    }
}

