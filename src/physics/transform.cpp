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

        void Transform::applyX(Transform const & t)
        {
            _pos.x += t._vel.x;
            _vel.x += t._acc.x;
        }

        void Transform::applyY(Transform const & t)
        {
            _pos.y += t._vel.y;
            _vel.y += t._acc.y;
        }

        void Transform::updateX()
        {
            _vel.x += _acc.x;
            _pos.x += _vel.x;
        }

        void Transform::updateY()
        {
            _vel.y += _acc.y;
            _pos.y += _vel.y;
        }

        void Transform::update()
        {
            _vel += _acc;
            _pos += _vel;
        }

        std::ostream & operator<<(std::ostream & os,
                    Transform const & t)
        {
            os << "Pos : (" << t.position().x << ", " << t.position().y << ") | ";
            os << "Vel : (" << t.velocity().x << ", " << t.velocity().y << ") | ";
            os << "Acc : (" << t.acceleration().x << ", " << t.acceleration().y << ")";
            return os;
        }
    }
}
