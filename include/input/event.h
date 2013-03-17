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
        // TODO: supprimer le contructeur par défaut, inclure le flags de front montant/descendant ou continu (enum avec FallingEdge, RisingEdge, Continuous)
        struct Event
        {
            typedef float Ratio;

            static Event::Ratio const Full;

            enum Id
            {
                Up, Down, Left, Right,
                A, B, X, Y, Z, Trigger,
                NextFrame, Attack, Damage,
                Enter, Leave
            };

            enum Edge
            {
                RisingEdge,
                FallingEdge,
                ContinuousEdge
            };

            Event() = default;
            Event(Event::Id, Event::Ratio, Event::Edge);
            Event(Event &&) = default;
            Event(const Event &) = default;
            ~Event() = default;
            Event & operator=(const Event &) = default;

            Event::Id id;
            Event::Ratio ratio;
            Event::Edge edge;
        };
    }
}

#endif

