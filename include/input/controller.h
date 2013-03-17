#ifndef INPUT_CONTROLLER_H_
#define INPUT_CONTROLLER_H_

#include <array>
#include <vector>
#include <unordered_map>
#include <SFML/Window/Event.hpp>
#include <config.h>
#include <input/event.h>

namespace EUSDAB
{
    class Entity;

    namespace Input
    {
        class State;
        class Speaker;

        class Controller
        {
            public:
                Controller(const std::array<Entity *, Config::NbPlayers> & players);
                Controller() = delete;
                Controller(Controller &&) = default;
                Controller(const Controller &) = delete;
                ~Controller();
                Controller & operator=(const Controller &) = delete;

                // Add an entity to the controller
                void addEntity(Entity *);
                void addEntity(Entity *, State *);

                // Must be called only once per frame
                //
                // FIXME replace with single/multiple pushEvent, 
                //   handle continuous events before update.
                //   Seriously, stop passing hard-typed containers, 
                //   use iterators instead.
                void pushEvent(const std::vector<sf::Event> &);

                // Update all speakers with current event context
                void update();

            protected:
                std::array<Speaker *, Config::NbPlayers> _playerList;
                std::vector<Speaker *> _entityList;

                // Configuration
                std::unordered_map<sf::Keyboard::Key, std::pair<Speaker * , 
                    Event::Id> , std::hash<int>> _keyMapping;
        };
    }
}

#endif
