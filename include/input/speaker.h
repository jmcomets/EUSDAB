#ifndef INPUT_SPEAKER_H_
#define INPUT_SPEAKER_H_

#include <queue>
#include <input/listener.h>

namespace EUSDAB
{
    namespace Input
    {
        // Event
        //
        // Structure corresponding to the event
        // given to the Speaker's event queue.
        struct Event
        {
            typedef float Ratio;
            enum Id
            {
                Up, Down, Left, Right,
                A, B, X, Y, Z,
                Trigger,
            };

            Event() = default;
            Event(Id, Ratio);
            Event(Event &&) = default;
            Event(const Event &) = default;
            ~Event() = default;
            Event & operator=(const Event &) = default;

            Id id;
            Ratio ratio;
        };

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
