#ifndef INPUT_CONTROLLER_H_
#define INPUT_CONTROLLER_H_

#include <type_traits>
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
                Controller() = delete;
                Controller(Controller &&) = default;
                Controller(const Controller &) = delete;
                Controller & operator=(const Controller &) = delete;

                Controller(const std::array<Entity *, Config::NbPlayers> & players);
                ~Controller();

                // Add an entity to the controller
                void addEntity(Entity *);
                void addEntity(Entity *, State *);

                // Push an event to the controller
                void pushEvent(const sf::Event &);
                template <typename InputIter>
                    void pushEvent(InputIter begin, InputIter end)
                {
                    using V = typename InputIter::value_type;
                    static_assert(std::is_convertible<const sf::Event &, V>::value, 
                        "Can only push `const sf::Event &` to Input::Controller");
                    for (; begin != end; begin++)
                    {
                        pushEvent(*begin);
                    }
                }

                // Update all speakers with current event context,
                //   must be called only once per frame.
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
