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
                Speaker();
                Speaker(Speaker &&) = default;
                Speaker(const Speaker &) = delete;
                ~Speaker() = default;
                Speaker & operator=(const Speaker &) = delete;
                void setListener(Listener *);
                void push(const Event &);
                void pollEvents();

            private:
                Listener * _listener;
                std::queue<Event> _events;
        };
    }
}

#endif
