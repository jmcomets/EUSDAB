#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <cmath>

namespace Geometry
{
    template <typename T>
    class Vector2
    {
        public:

            Vector2(T const & x = 0, T const & y = 0):
                _x(x), _y(y)
            {
            }

            Vector2(Vector2 &&) = default;
            Vector2(Vector2 const &) = default;
            ~Vector2() = default;
            Vector2 & operator=(Vector2 const &) = default;

            template <typename U>
            Vector2 & operator+=(Vector2<U> const & v)
            {
                _x += v.x();
                _y += v.y();
                return *this;
            }

            template <typename U>
            Vector2 & operator-=(Vector2<U> const & v)
            {
                _x -= v.x();
                _y -= v.y();
                return *this;
            }

            template <typename U>
            Vector2 & operator*=(U const & u)
            {
                _x *= u;
                _y *= u;
                return *this;
            }

            template <typename U>
            Vector2 & operator/=(U const & u)
            {
                _x /= u;
                _y /= u;
                return *this;
            }

            template <typename U>
            bool operator==(Vector2<U> const & v) const
            {
                return v._x == _x && v._y == _y;
            }

            template <typename U>
            bool operator!=(Vector2<U> const & v) const
            {
                return !(*this == v);
            }

            T const & x() const
            {
                return _x;
            }

            T const & x(T const & x)
            {
                return _x = x;
            }

            T const & y() const
            {
                return _y;
            }

            T const & y(T const & y)
            {
                return _y = y;
            }

            double norm() const
            {
                return std::sqrt(_x * _x + _y * _y);
            }

            Vector2 unit() const
            {
                double s = norm();
                return (s > 0) ? Vector2(*this / s) : Vector2();
            }

            template <typename U>
            T const & dot(Vector2<U> const & v) const
            {
                return _x * v.x() + _y * v.y();
            }

            template <typename U>
            Vector2 & translate(Vector2<U> const & v)
            {
                _x += v.x();
                _y += v.y();
                return *this;
            }

            Vector2 perp()
            {
                return Vector2(*this).rotate(M_PI / 2.0);
            }

            template <typename U>
            Vector2 & rotate(U const & angle, Vector2<T> const & origin = Vector2<T>())
            {
                if (origin != *this)
                {
                    T x = _x;

                    _x = (x - origin.x()) * std::cos(angle)
                        - (_y - origin.y()) * std::sin(angle);

                    _y = (x - origin.x()) * std::sin(angle)
                        + (_y - origin.y()) * std::cos(angle);
                }
                return *this;
            }

        private:
            T _x;
            T _y;
    };

    template <typename T, typename U>
    inline Vector2<T> operator+(Vector2<T> lv, Vector2<U> const & rv)
    {
        return lv += rv;
    }

    template <typename T, typename U>
    inline Vector2<T> operator-(Vector2<T> lv, Vector2<U> const & rv)
    {
        return lv -= rv;
    }

    template <typename T, typename U>
    inline Vector2<T> operator*(Vector2<T> v, U const & u)
    {
        return v *= u;
    }

    template <typename T, typename U>
    inline Vector2<T> operator/(Vector2<T> v, U const & u)
    {
        return v /= u;
    }
}


#endif
