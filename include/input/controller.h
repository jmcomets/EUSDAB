#ifndef INPUT_CONTROLLER_H_
#define INPUT_CONTROLLER_H_

#include <vector>
#include <map>
#include <SFML/Window/Event.hpp>
#include <entity.h>
#include <input/event.h>
#include <input/state.h>
#include <input/speaker.h>

namespace EUSDAB
{
    namespace Input
    {
        class Controller
        {
            public:
                Controller(Controller &&) = default;
                Controller(Controller const &) = delete;
                Controller & operator=(Controller const &) = delete;

                Controller() = default;
                ~Controller();

                template <typename InputIter>
                    Controller(InputIter begin, InputIter end):
                        Controller()
                {
                    for(; begin != end; begin++)
                    {
                        Entity * e = *begin;
                        Speaker * s = speaker(e);
                        _playerList.push_back(s);
                    }
                    initMappings();
                }

                // Add an entity to the controller
                void addEntity(Entity *);

                // Push an event to the controller
                // ...SFML event
                void pushEvent(sf::Event const &);
                // ...EUSDAB event (for a specific Entity)
                void pushEvent(Entity *, Event const &);

                template <typename InputIter>
                    void pushEvent(InputIter begin, InputIter end)
                {
                    for (; begin != end ; begin++)
                    {
                        pushEvent(*begin);
                    }
                }

                // Update all speakers with current event context,
                //   must be called only once per frame.
                void update();

                // Get the Entity's Speaker lazily
                Speaker * speaker(Entity *);

            protected:
                void initMappings();

            private:
                std::map<Entity *, Speaker *> _allSpeakers;
                std::vector<Speaker *> _playerList;
                std::vector<Speaker *> _speakerList;

                std::map<sf::Keyboard::Key, 
                    std::pair<Speaker *, Event::Id>> _keyMapping;
        };
    }
}

#endif
