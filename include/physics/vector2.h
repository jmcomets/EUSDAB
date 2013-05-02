#ifndef PHYSICS_VECTOR2_H_
#define PHYSICS_VECTOR2_H_

#include <cmath>
#include <stdexcept>

namespace EUSDAB
{
    namespace Physics
    {
        template <typename T>
            class Vector2T
        {
            public:
                // Access corresponding types from within 
                //  class instanciation (don't use extra templates).
                typedef T Unit;

                Vector2T(const Unit & x, const Unit & y):
                    _x(x), _y(y)
                {
                }

                Vector2T() = default;
                Vector2T(Vector2T<Unit> &&) = default;
                Vector2T(const Vector2T<Unit> &) = default;
                ~Vector2T() = default;
                Vector2T<Unit> & operator=(const Vector2T<Unit> &) = default;

                bool operator==(const Vector2T<Unit> & v) const
                {
                    return _x == v._x && _y == v._y;
                }

                bool operator!=(const Vector2T<Unit> & v) const
                {
                    return !(*this == v);
                }

                Vector2T<Unit> & operator+=(const Vector2T<Unit> & v)
                {
                    _x += v._x;
                    _y += v._y;
                    return *this;
                }

                Vector2T<Unit> & operator-=(const Vector2T<Unit> & v)
                {
                    _x -= v._x;
                    _y -= v._y;
                   return *this;
                }

                Vector2T<Unit> & operator*=(const Unit & scale)
                {
                    _x *= scale;
                    _y *= scale;
                    return *this;
                }

                Vector2T<Unit> & operator/=(const Unit & scale)
                {
                    if (scale == static_cast<Unit>(0))
                    {
                        throw std::overflow_error("Cannot divide by zero");
                    }
                    _x /= scale;
                    _y /= scale;
                    return *this;
                }

                Vector2T<Unit> operator+(const Vector2T<Unit> & v) const
                {
                    return Vector2T<Unit>(*this) += v;
                }

                Vector2T<Unit> operator-(const Vector2T<Unit> & v) const
                {
                    return Vector2T<Unit>(*this) -= v;
                }

                Vector2T<Unit> operator*(const Unit & scale) const
                {
                    return Vector2T<Unit>(*this) *= scale;
                }

                Vector2T<Unit> operator/(const Unit & scale) const
                {
                    return Vector2T<Unit>(*this) /= scale;
                }

                template <typename U>
                    operator Vector2T<U>() const
                {
                    return Vector2T<U>(static_cast<U>(_x), static_cast<U>(_y));
                }

                // Get/Set the Vector's x coordinate
                Unit x() const
                {
                    return _x;
                }

                void setX(const Unit & x)
                {
                    _x = x;
                }

                // Get/Set the Vector's y coordinate
                Unit y() const
                {
                    return _y;
                }

                void setY(const Unit & y)
                {
                    _y = y;
                }

                Vector2T<Unit> & translate(Vector2T<Unit> const & v)
                {
                    return *this += v;
                }

                Vector2T<Unit> & translate(const Unit & x, const Unit & y)
                {
                    return translate(Vector2T<Unit>(x, y));
                }

                template <typename U>
                    U norm() const
                {
                    return std::sqrt(_x*_x + _y*_y);
                }

            private:
                Unit _x, _y;
        };
    }
}

#endif
