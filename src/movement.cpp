#include <movement.h>

namespace EUSDAB
{
    Movement::Movement(Movement::Flag f):
        _flag(f)
    {
    }

    Movement::Flag Movement::flag() const
    {
        return _flag;
    }

    void Movement::setFlag(Movement::Flag f)
    {
        _flag = f;
    }

    Movement::operator Movement::Flag() const
    {
        return flag();
    }
}
