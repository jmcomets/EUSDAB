#ifndef PHYSICS_AABB_H_
#define PHYSICS_AABB_H_

namespace EUSDAB
{
    namespace Physics
    {
        template <typename T>
            class AABB
        {
            public:
                AABB(const T & x, const T & y, const T & w, const T & h):
                    _x(x), _y(y),
                    _w(w), _h(h)
                {
                }

                AABB(const AABB &) = default;
                AABB(AABB &&) = default;

                AABB & operator=(const AABB &) = default;

                ~AABB() = default;

                const T & x() const
                {
                    return _x;
                }

                void setX(const T & x)
                {
                    _x = x;
                }

                const T & y() const
                {
                    return _y;
                }

                void setY(const T & y)
                {
                    _y = y;
                }

                const T & width() const
                {
                    return _w;
                }

                void setWidth(const T & w)
                {
                    _w = w;
                }

                const T & height() const
                {
                    return _h;
                }

                void setHeight(const T & h)
                {
                    _h = h;
                }

                bool collides(const AABB<T> & other) const
                {
                    return ((_x >= other._x + other._w)
                            || (_x + _w <= other._x)
                            || (_y >= other._y + other._h)
                            || (_y + _h <= other._y)) == false;
                }

                void translate(const T & x, const T & y)
                {
                    _x += x;
                    _y += y;
                }

            private:
                T _x, _y;
                T _w, _h;
        };
    }
}

#endif

