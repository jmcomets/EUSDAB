#include <component.h>

namespace EUSDAB
{
    namespace Physics
    {
        Component::Component() :
            _pos(),
            _vel(),
            _acc()
        {
        }

        Vector2 const & Component::position() const
        {
            return _pos;
        }

        Vector2 & Component::position();
        {
            return _pos;
        }


        Vector2 const & Component::velocity() const
        {
            return _vel;
        }

        Vector2 & Component::velocity()
        {
            return _vel;
        }


        Vector2 const & Component::acceleration() const
        {
            return _acc;
        }

        Vector2 & Component::acceleration()
        {
            return _acc;
        }


        void Component::update()
        {
            _vel += _acc;
            _pos += _vel;
        }
    }
}
