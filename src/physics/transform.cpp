#include <physics/transform.h>

namespace EUSDAB
{
    namespace Physics
    {
        Transform::Transform(Vector2 const & pos,
                Vector2 const & vel,
                Vector2 const & acc):
            _pos(pos),
            _vel(vel),
            _acc(acc)
        {
        }

        Vector2 const & Transform::position() const
        {
            return _pos;
        }

        Vector2 & Transform::position()
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

        void Transform::apply(Transform const & t)
        {
            _pos += t._vel;
            _vel += t._acc;
        }

        void Transform::update()
        {
            _vel += _acc;
            _pos += _vel;
        }
    }
}
