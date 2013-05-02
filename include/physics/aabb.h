#ifndef PHYSICS_AABB_H_
#define PHYSICS_AABB_H_

#include <physics/vector2.h>

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

                AABBT(const Unit & x, const Unit & y, const Unit & w, const Unit & h):
                    _x(x), _y(y),
                    _w(w), _h(h)
                {
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

                void setX(const Unit & x)
                {
                    _x = x;
                }

                // Get/Set the AABB's y coordinate (center)
                Unit y() const
                {
                    return _y;
                }

                void setY(const Unit & y)
                {
                    _y = y;
                }

                // Get/Set the AABB's width
                Unit width() const
                {
                    return _w;
                }

                void setWidth(const Unit & w)
                {
                    _w = w;
                }

                // Get/Set the AABB's height
                Unit height() const
                {
                    return _h;
                }

                void setHeight(const Unit & h)
                {
                    _h = h;
                }

                // Check if collides with another AABB
                bool collides(const AABBT<Unit> & aabb) const
                {
                    return ((_x >= aabb._x + aabb._w)
                            || (_x + _w <= aabb._x)
                            || (_y >= aabb._y + aabb._h)
                            || (_y + _h <= aabb._y)) == false;
                }

                void translate(const Unit & x, const Unit & y)
                {
                    _x += x;
                    _y += y;
                }

                Vector2 center() const
                {
                    return Vector2(_x, _y);
                }

            private:
                Unit _x, _y;
                Unit _w, _h;
        };
    }
}

#endif
