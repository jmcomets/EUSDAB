#include <transform.h>

namespace EUSDAB
{
    namespace Physics
    {
        Transform::Transform() :
            _pos(),
            _vel(),
            _acc()
        {
        }

        Vector2 const & Transform::position() const
        {
            return _pos;
        }

        Vector2 & Transform::position();
        {
            return _pos;
        }


        Vector2 const & Transform::velocity() const
        {
            return _vel;
        }

        Vector2 & Transform::velocity()
        {
            return _vel;
        }


        Vector2 const & Transform::acceleration() const
        {
            return _acc;
        }

        Vector2 & Transform::acceleration()
        {
            return _acc;
        }


        void Transform::update()
        {
            _vel += _acc;
            _pos += _vel;
        }
    }
}
