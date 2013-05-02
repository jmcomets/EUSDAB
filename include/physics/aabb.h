#ifndef PHYSICS_AABB_H_
#define PHYSICS_AABB_H_

#include <physics/vector2.h>
#include <cassert>

namespace EUSDAB
{
    namespace Physics
    {
        template <typename T>
            class AABBT
        {
            public:
                // Access corresponding types from within 
                //  class instanciation (don't use extra templates).
                typedef T Unit;
                typedef Vector2T<Unit> Vector2;

                AABBT():
                    _x(0), _y(0),
                    _w(0), _h(0)
                {
                }

                // Construct from center and dimensions
                AABBT(const Vector2 & center, const Unit & w, const Unit & h):
                    _x(center.x() - w / static_cast<Unit>(2)),
                    _y(center.y() - w / static_cast<Unit>(2)),
                    _w(w), _h(h)
                {
                }

                // Construct from top-left position and dimensions
                AABBT(const Unit & x, const Unit & y, const Unit & w, const Unit & h):
                    _x(x), _y(y),
                    _w(w), _h(h)
                {
                    assert(w >= static_cast<Unit>(0));
                    assert(h >= static_cast<Unit>(0));
                }

                AABBT(AABBT &&) = default;
                AABBT(const AABBT &) = default;
                ~AABBT() = default;
                AABBT & operator=(const AABBT &) = default;

                // Get/Set the AABB's x coordinate (center)
                Unit x() const
                {
                    return _x;
                }

                AABBT<Unit> & setX(const Unit & x)
                {
                    _x = x;
                    return *this;
                }

                // Get/Set the AABB's y coordinate (center)
                Unit y() const
                {
                    return _y;
                }

                AABBT<Unit> & setY(const Unit & y)
                {
                    _y = y;
                    return *this;
                }

                // Get the AABB's width
                Unit width() const
                {
                    return _w;
                }
                // ...get half of width
                Unit halfwidth() const
                {
                    return _w / static_cast<Unit>(2);
                }
                // ...set width
                AABBT<Unit> & setWidth(const Unit & w)
                {
                    _w = w;
                    return *this;
                }
                // ...get half of width

                // Get the AABB's height
                Unit height() const
                {
                    return _h;
                }
                // ...get half of height
                Unit halfheight() const
                {
                    return _h / static_cast<Unit>(2);
                }
                // ...set height
                AABBT<Unit> & setHeight(const Unit & h)
                {
                    _h = h;
                    return *this;
                }

                // Check if collides with another AABB
                bool collides(const AABBT<Unit> & aabb) const
                {
                    return ((_x >= aabb._x + aabb._w)
                            || (_x + _w <= aabb._x)
                            || (_y >= aabb._y + aabb._h)
                            || (_y + _h <= aabb._y)) == false;
                }

                AABBT<Unit> & translate(const Unit & x, const Unit & y)
                {
                    _x += x;
                    _y += y;
                    return *this;
                }

                // Return the AABB's center
                Vector2 center() const
                {
                    return Vector2(_x + halfwidth(), _y + halfheight());
                }

            private:
                Unit _x, _y;
                Unit _w, _h;
        };
    }
}

#endif
