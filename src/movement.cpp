#include <movement.h>
#include <cstddef>

namespace EUSDAB
{
    // Check that Flag can contain every Action / Direction
    static constexpr std::size_t NoopIndex = static_cast<std::size_t>(18);
    static_assert(Movement::Noop == (1 << NoopIndex),
            "NoopIndex must be the index of the Movement::Noop bit");
    static_assert(sizeof(Movement::Flag) * 8 >= NoopIndex, 
            "Overflow in Movement::Flag, consider using a bigger integer");

    Movement::Movement(Movement::Flag f):
        _action(static_cast<Action>(0)),
        _direction(static_cast<Direction>(0))
    {
        setFlag(f);
    }

    Movement::Movement(Movement::Action act, Movement::Direction dir):
        _action(act), _direction(dir)
    {
    }

    Movement::Flag Movement::flag() const
    {
        return _action | _direction;
    }

    void Movement::setFlag(Movement::Flag f)
    {
        setAction(toAction(f));
        setDirection(toDirection(f));
    }

    Movement::operator Movement::Flag() const
    {
        return flag();
    }

    bool Movement::operator<(const Movement & mvt) const
    {
        return flag() < mvt.flag();
    }

    void Movement::setAction(Movement::Action act)
    {
        _action = act;
    }

    void Movement::setDirection(Movement::Direction dir)
    {
        _direction = dir;
    }

    static constexpr std::size_t NoneIndex = static_cast<std::size_t>(4);
    static_assert(Movement::None == (1 << NoneIndex),
            "NoneIndex must be the index of the Movement::None bit");
    static constexpr Movement::Flag SeparationMask = ~static_cast<Movement::Flag>(0) 
        << NoneIndex;

    Movement::Action Movement::toAction(Movement::Flag f) const
    {
        return static_cast<Action>(f & SeparationMask);
    }

    Movement::Direction Movement::toDirection(Movement::Flag f) const
    {
        return static_cast<Direction>(f & ~SeparationMask);
    }

    Movement::Direction Movement::direction() const
    {
        return _direction;
    }

    Movement::Action Movement::action() const
    {
        return _action;
    }
}
