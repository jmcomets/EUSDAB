#include <movement.h>

namespace EUSDAB
{
    Movement::Movement(Movement::Action action, Movement::Direction direction):
        action(action),
        direction(direction)
    {
    }

    Movement::operator int() const
    {
        return action | direction;
    }
}

