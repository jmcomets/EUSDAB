#include <movement.h>
#include <cstddef>
#ifdef DEBUG
#  include <sstream>
#endif

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

#ifdef DEBUG
    std::string Movement::debug() const
    {
        std::ostringstream oss;
        oss << "<Movement address=" << this << ", action=[";
        oss << " " << debugAction(_action) << " ](" << _action 
            << "), direction=[" << debugDirection(_direction);
        oss << " ](" << _direction << ")>";
        return oss.str();
    }

    static auto addToRepr = [](std::string & repr,
            const std::string & str)
    {
        if (repr.empty() == false) { repr += " | "; }
        repr += str;
    };

    std::string Movement::debugAction(Movement::Action act) const
    {
        std::string repr;
        if ((act & Idle)        != 0) { addToRepr(repr, "Idle"); }
        if ((act & Jump)        != 0) { addToRepr(repr, "Jump"); }
        if ((act & Attack)      != 0) { addToRepr(repr, "Attack"); }
        if ((act & Smash)       != 0) { addToRepr(repr, "Smash"); }
        if ((act & Flee)        != 0) { addToRepr(repr, "Flee"); }
        if ((act & Guard)       != 0) { addToRepr(repr, "Guard"); }
        if ((act & OnHit)       != 0) { addToRepr(repr, "OnHit"); }
        if ((act & Walk)        != 0) { addToRepr(repr, "Walk"); }
        if ((act & Run)         != 0) { addToRepr(repr, "Run"); }
        if ((act & Falling)     != 0) { addToRepr(repr, "Falling"); }
        if ((act & Crouch)      != 0) { addToRepr(repr, "Crouch"); }
        if ((act & AerialHit)   != 0) { addToRepr(repr, "AerialHit"); }
        if ((act & AerialAttack)   != 0) { addToRepr(repr, "AerialAttack"); }
        if ((act & Special)     != 0) { addToRepr(repr, "Special"); }
        //if ((act & Grab)        != 0) { addToRepr(repr, "Grab"); }
        //if ((act & Haul)        != 0) { addToRepr(repr, "Haul"); }
        return repr;
    }

    std::string Movement::debugDirection(Movement::Direction dir) const
    {
        std::string repr;
        if ((dir & Up)    != 0) { addToRepr(repr, "Up"); }
        if ((dir & Down)  != 0) { addToRepr(repr, "Down"); }
        if ((dir & Left)  != 0) { addToRepr(repr, "Left"); }
        if ((dir & Right) != 0) { addToRepr(repr, "Right"); }
        return repr;
    }

    std::string Movement::debugFlag(Movement::Flag f) const
    {
        std::string repr;
        repr += "(action = [";
        repr += debugAction(toAction(f));
        repr += "], direction = [";
        repr += debugDirection(toDirection(f));
        repr += "])";
        return repr;
    }
#endif
}
