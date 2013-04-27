#ifndef INPUT_EVENT_H
#define INPUT_EVENT_H

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

            static Ratio const Full;

            enum Id
            {
                Up, Down, Left, Right,
                A, B, X, Y, Z, Trigger,
                NextFrame, Attack, Damage,
                Grab, Ground, Collide,
                Enter, Leave
            };

            enum Edge
            {
                RisingEdge,
                FallingEdge,
                ContinuousEdge
            };

            Event() = delete;
            Event(Event &&) = default;
            Event(const Event &) = default;
            ~Event() = default;
            Event & operator=(const Event &) = default;

            Event(Id, Ratio, Edge);

            Id id;
            Ratio ratio;
            Edge edge;
        };
    }
}

#endif

