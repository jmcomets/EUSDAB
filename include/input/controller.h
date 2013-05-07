#ifndef INPUT_CONTROLLER_H_
#define INPUT_CONTROLLER_H_

#include <vector>
#include <set>
#include <map>
#include <SFML/Window/Event.hpp>
#include <input/event.h>
#include <input/speaker.h>
#include <state.h>

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

                Controller();
                ~Controller() = default;

                template <typename InputIter>
                    Controller(InputIter begin, InputIter end):
                        _playerList(),
                        _allSpeakers(),
                        _keyMapping()
                {
                    for(; begin != end; begin++)
                    {
                        Speaker * s = *begin;
                        addSpeaker(s);
                        _playerList.push_back(s);
                    }
                    initMappings();
                }

                // Add an speaker to the controller
                void addSpeaker(Speaker *);

                // Push an event to the controller
                // ...SFML event
                void pushEvent(const sf::Event &);
                // ...EUSDAB event (for a specific Speaker)
                void pushEvent(Speaker *, const Event &);

                // Shortcut for signaling next frame
                void nextFrame();

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

            protected:
                // Initialize mappings (ugly ugly ugly)
                void initMappings();

            private:
                std::vector<Speaker *> _playerList;
                std::set<Speaker *> _allSpeakers;

                std::map<sf::Keyboard::Key, 
                    std::pair<Speaker *, Event::Id>> _keyMapping;
        };
    }
}

#endif
