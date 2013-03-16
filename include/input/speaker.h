#ifndef INPUT_SPEAKER_H_
#define INPUT_SPEAKER_H_

#include <queue>

#include <input/listener.h>
#include <input/event.h>

namespace EUSDAB
{
    namespace Input
    {
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

                void setListener(Listener *);

                void push(Event const &);
                void pollEvents();

            private:
                Listener * _listener;
                std::queue<Event> _events;
        };
    }
}

#endif

