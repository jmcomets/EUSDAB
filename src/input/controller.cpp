#include <input/controller.h>

#include <entity.h>
#include <input/listener.h>
#include <input/state.h>
#include <input/speaker.h>

namespace EUSDAB
{
    namespace Input
    {
        Controller::Controller(std::array<Entity *, Config::NbPlayers> const & players):
            _playerList(), _entityList(),
            _keyMapping()
        {
            // Remplissage de players (et de ta mère JM)
            _playerList.fill(nullptr);
            for(std::size_t i = 0 ; i < _playerList.size() ; ++i)
                if(players[i] != nullptr)
                {
                    players[i]->state()->entity(players[i]);
                    _playerList[i] = new Speaker(players[i]->state());
                }

            // Mapping des touches claviers
            // TODO finir
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
            for(auto e : _playerList)
            {
                delete e;
            }
            for(auto e : _entityList)
            {
                delete e;
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

            for (auto s : _playerList)
            {
                if (s != nullptr)
                {
                    s->pollEvents();
                }
            }

            for (auto s : _entityList)
            {
                s->pollEvents();
            }
        }

        void Controller::addEntity(Entity * e)
        {
            _entityList.push_back(new Speaker(e->state()));
        }

        void Controller::addEntity(Entity * e, State * s)
        {
            e->state(s);
            s->entity(e);
            _entityList.push_back(new Speaker(s));
        }

        void Controller::pushEvent(const sf::Event & e)
        {
            if (e.type == sf::Event::KeyPressed)
            {
                auto it = _keyMapping.find(e.key.code);
                if (it != _keyMapping.end())
                {
                    Event event(it->second.second, Event::Full, Event::RisingEdge);
                    it->second.first->push(event);
                }
            }
            if (e.type == sf::Event::KeyReleased)
            {
                auto it = _keyMapping.find(e.key.code);
                if (it != _keyMapping.end())
                {
                    Event event(it->second.second, Event::Full, Event::FallingEdge);
                    it->second.first->push(event);
                }
            }

            // TODO Joystick : rising and falling edge
        }
    }
}
