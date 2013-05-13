#ifndef INPUT_CONTROLLER_H_
#define INPUT_CONTROLLER_H_

#include <vector>
#include <set>
#include <map>
#include <SFML/Window/Event.hpp>
#include <input/event.h>
#include <input/speaker.h>
#include <state.h>
#include <input/mapping.h>

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

                Controller(Mapping *);
                ~Controller();

                template <typename InputIter>
                    Controller(InputIter begin, InputIter end, Mapping * mapping):
                        _allSpeakers(),
                        _mapping(mapping)
                {
                    assert(_mapping != nullptr);
                    for (; begin != end; begin++)
                    {
                        Speaker * s = *begin;
                        addSpeaker(s);
                    }
                }

                // Add an speaker to the controller
                void addSpeaker(Speaker *);
                // ...range version
                template <typename InputIter>
                    void addSpeaker(InputIter begin, InputIter end)
                {
                    for (; begin != end; begin++)
                    {
                        addSpeaker(*begin);
                    }
                }

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

            private:
                std::set<Speaker *> _allSpeakers;
                Mapping * _mapping;
        };
    }
}

#endif
