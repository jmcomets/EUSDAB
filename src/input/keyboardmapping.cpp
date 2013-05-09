#include <input/keyboardmapping.h>
#include <cassert>

namespace EUSDAB
{
    namespace Input
    {
        KeyboardMapping::KeyboardMapping() : Mapping(), _keyMapping()
        {
        }

        KeyboardMapping::~KeyboardMapping()
        {
        }

        void KeyboardMapping::pushEvent(sf::Event const & event)
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
        }

        void KeyboardMapping::update()
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
        }
        

        void KeyboardMapping::initMappings()
        {
            assert (_playerList.size() > 1);

            _keyMapping[sf::Keyboard::Z] = std::make_pair(_playerList.at(0), Event::Up);
            _keyMapping[sf::Keyboard::S] = std::make_pair(_playerList.at(0), Event::Down);
            _keyMapping[sf::Keyboard::Q] = std::make_pair(_playerList.at(0), Event::Left);
            _keyMapping[sf::Keyboard::D] = std::make_pair(_playerList.at(0), Event::Right);

            _keyMapping[sf::Keyboard::Up]    = std::make_pair(_playerList.at(1), Event::Up);
            _keyMapping[sf::Keyboard::Down]  = std::make_pair(_playerList.at(1), Event::Down);
            _keyMapping[sf::Keyboard::Left]  = std::make_pair(_playerList.at(1), Event::Left);
            _keyMapping[sf::Keyboard::Right] = std::make_pair(_playerList.at(1), Event::Right);
        }
    }
}
