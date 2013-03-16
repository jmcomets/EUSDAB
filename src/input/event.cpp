#include <input/event.h>

namespace EUSDAB
{
    namespace Input
    {
        Event::Ratio const Full = 1.0;

        Event::Event(Id id, Ratio ratio):
            id(id), ratio(ratio)
        {
        }
    }
}
