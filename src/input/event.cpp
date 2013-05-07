#include <input/event.h>

namespace EUSDAB
{
    namespace Input
    {
        Event::Event(Event::Id id, Event::Ratio ratio, Event::Edge edge):
            id(id),
            ratio(ratio),
            edge(edge)
        {
        }
    }
}
