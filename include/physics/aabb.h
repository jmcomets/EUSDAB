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

                AABBT(const Vector2 & center,
                        const Unit & w, const Unit & h):
                    _x(center.x),
                    _y(center.y),
                    _w(w), _h(h)
                {
                    assert(w >= static_cast<Unit>(0));
                    assert(h >= static_cast<Unit>(0));
                }

                AABBT(const Unit & x, const Unit & y,
                        const Unit & w, const Unit & h):
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
                    assert(w >= static_cast<Unit>(0));
                    _w = w;
                    return *this;
                }

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
                    assert(h >= static_cast<Unit>(0));
                    _h = h;
                    return *this;
                }

                // Check if excludes another AABB (ie: doesn't
                //  contain or overlap)
                bool excludes(const AABBT<Unit> & aabb) const
                {
                    return collides(aabb) == false;
                }

                // Check if collides with another AABB
                bool collides(const AABBT<Unit> & aabb) const
                {
                    Vector2 topLeft = min();
                    Vector2 aabbTopLeft = aabb.min();
                    Vector2 bottomRight = max();
                    Vector2 aabbBottomRight = aabb.max();
                    return (bottomRight.x < aabbTopLeft.x ||
                            bottomRight.y < aabbTopLeft.y ||
                            topLeft.x > aabbBottomRight.x ||
                            topLeft.y > aabbBottomRight.y) == false;
                }

                // Check if contains another AABB (ie: contains both
                //  extreme corners)
                bool contains(const AABBT<Unit> & aabb) const
                {
                    return contains(aabb.min()) && contains(aabb.max());
                }

                // Check if contains a point
                bool contains(const Vector2 & p) const
                {
                    Vector2 topLeft = min();
                    Vector2 bottomRight = max();
                    return (topLeft.x <= p.x &&
                            topLeft.y <= p.y &&
                            p.x <= bottomRight.x &&
                            p.y <= bottomRight.y) == false;
                }

                // Merge the AABB with another
                void merge(const AABBT<Unit> & aabb)
                {
                    // Store both corners
                    Vector2 topLeft = min();
                    Vector2 aabbTopLeft = aabb.min();
                    Vector2 bottomRight = max();
                    Vector2 aabbBottomRight = aabb.max();

                    // Compute new corners
                    Unit minX = std::min(topLeft.x, aabbTopLeft.x);
                    Unit minY = std::min(topLeft.y, aabbTopLeft.y);
                    Unit maxX = std::max(bottomRight.x, aabbBottomRight.x);
                    Unit maxY = std::max(bottomRight.y, aabbBottomRight.y);

                    // Update data
                    _w = maxX - minX; assert(_w >= static_cast<Unit>(0));
                    _h = maxY - minY; assert(_h >= static_cast<Unit>(0));
                    _x = minX + _w / static_cast<Unit>(2);
                    _y = minY + _h / static_cast<Unit>(2);
                }

                // Translate the AABB by a given vector
                AABBT<Unit> & translate(const Unit & x, const Unit & y)
                {
                    _x += x;
                    _y += y;
                    return *this;
                }
                // ...overload with Vector2
                AABBT<Unit> & translate(const Vector2 & v)
                {
                    return translate(v.x(), v.y());
                }

                // Return the AABB's center
                Vector2 center() const
                {
                    return Vector2(_x, _y);
                }

                // Return the AABB's top-left corner
                Vector2 min() const
                {
                    return Vector2(_x - _w / static_cast<Unit>(2),
                            _y - _h / static_cast<Unit>(2));
                }

                // Return the AABB's bottom-right corner
                Vector2 max() const
                {
                    return Vector2(_x + _w / static_cast<Unit>(2),
                            _y + _h / static_cast<Unit>(2));
                }

            private:
                Unit _x, _y;
                Unit _w, _h;
        };
    }
}

#endif
