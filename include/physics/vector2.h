#ifndef PHYSICS_VECTOR2_H_
#define PHYSICS_VECTOR2_H_

#include <cctype>

namespace EUSDAB
{
    namespace Physics
    {
        template<typename T>
            class Vector2
        {
            public:
                Vector2(T const && x = T(), T const && y = T()):
                    _x(x),
                    _y(y)
                {
                }

                Vector2(Vector2 const &) = default;
                Vector2(Vector2 &&) = default;
                Vector2 & operator=(Vector2 const &) = default;
                ~Vector2() = default;

                T const & x() const
                {
                    return _x;
                }

                T const & y() const
                {
                    return _y;
                }

                void x(T const & x)
                {
                    _x = x;
                }

                void y(T const & y)
                {
                    _y = y;
                }

                bool operator==(Vector2 const & other)
                {
                    return _x == other._x && _y == other._y;
                }

                bool operator!=(Vector2 const & other)
                {
                    return !this->operator==(other);
                }

                Vector2 & operator+=(Vector2 const & other)
                {
                    _x += other._x;
                    _y += other._y;
                    return *this;
                }

                Vector2 & operator-=(Vector2 const & other)
                {
                    _x -= other._x;
                    _y -= other._y;
                   return *this;
                }

                Vector2 & operator*=(T const & scale)
                {
                    _x *= scale;
                    _y *= scale;
                    return *this;
                }

                Vector2 & operator/=(T const & scale)
                {
                    _x /= scale;
                    _y /= scale;
                    return *this;
                }

                template <typename U>
                    operator Vector2<U>()
                {
                    Vector2<U> v;
                    v.x(static_cast<U>(_x));
                    v.y(static_cast<U>(_y));
                    return v;
                }

                Vector2 & translate(T const & tx, T const & ty)
                {
                    _x += tx;
                    _y += ty;
                    return *this;
                }

                Vector2 & translate(Vector2<T> const & t)
                {
                    translate(t._x, t._y);
                    return *this;
                }

            private:
                T _x;
                T _y;
        };

        template <typename T>
            inline Vector2<T> operator+(Vector2<T> l, Vector2<T> const & r)
        {
            return l += r;
        }

        template <typename T>
            inline Vector2<T> operator-(Vector2<T> l, Vector2<T> const & r)
        {
            return l -= r;
        }

        template <typename T>
            inline Vector2<T> operator*(Vector2<T> l, T const & r)
        {
            return l *= r;
        }

        template <typename T>
            inline Vector2<T> operator/(Vector2<T> l, T const & r)
        {
            return l /= r;
        }
    }
}

#endif

