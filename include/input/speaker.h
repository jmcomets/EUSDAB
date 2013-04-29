#ifndef INPUT_SPEAKER_H_
#define INPUT_SPEAKER_H_

#include <queue>

#include <input/event.h>

namespace EUSDAB
{
    namespace Input
    {
        class Listener;

        // Speaker
        //
        // Dispatches different Events to Listeners,
        // simulates a state-based event handling.
        class Speaker
        {
            public:
                Speaker(Speaker &&) = default;
                Speaker(Speaker const &) = delete;
                ~Speaker() = default;
                Speaker & operator=(Speaker const &) = delete;

                Speaker(Listener * listener = nullptr);

                // Change the Speaker's current Listenrr
                void setListener(Listener *);

                // Push an Event to the Speaker's input queue
                void push(const Event &);

                // Dispatch all Events to current Listener
                void pollEvents();

            private:
                Listener * _listener;
                std::queue<Event> _events;
        };
    }
}

#endif
