#ifndef INPUT_CONTROLLER_H_
#define INPUT_CONTROLLER_H_

#include <SFML/Window/Event.hpp>

#include <type_traits>
#include <vector>
#include <unordered_map>

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
                Controller(Controller const &) = delete;
                Controller & operator=(Controller const &) = delete;

                Controller(std::vector<Entity *> const & players);
                ~Controller();

                // Add an entity to the controller
                void addEntity(Entity *);
                void addEntity(Entity *, State *);

                // Push an event to the controller
                void pushEvent(Input::Event const &);
                void pushEvent(sf::Event const &);

                template <typename InputIter>
                    void pushEvent(InputIter begin, InputIter end)
                {
                    //using V = typename InputIter::value_type;
                    typedef typename InputIter::value_type V;
                    static_assert(std::is_convertible<const sf::Event &, V>::value, 
                        "Can only push `sf::Event const &` to Input::Controller");
                    for (; begin != end ; begin++)
                    {
                        pushEvent(*begin);
                    }
                }

                // Update all speakers with current event context,
                //   must be called only once per frame.
                void update();

            protected:
                std::vector<Speaker *> _playerList;
                std::vector<Speaker *> _entityList;

                // Configuration
                std::unordered_map<sf::Keyboard::Key, std::pair<Speaker * , 
                    Event::Id> , std::hash<int>> _keyMapping;
        };
    }
}

#endif
