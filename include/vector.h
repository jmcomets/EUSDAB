#ifndef VECTOR_H_INCLUDED_
#define VECTOR_H_INCLUDED_

#include <cmath>
#include <limits>

namespace Geometry
{
    template <class T>
        struct Vector
    {
        T x, y;

        Vector(): x(0), y(0)
        {
        }

        Vector(T x = 0, T y = 0):
            x(x), y(y)
        {
        }

        /* virtual */ ~Vector()
        {
        }

        T dot(const Vector<T> & v) const
        {
            return x * v.x + y * v.y;
        }

        template <class U>
            Vector<T> & rotate(U angle, const Vector<T> & origin = Vector<T>())
        {
            T selfX = x;
            x = (selfX - origin.x) * std::cos(angle) 
                - (y - origin.y) * std::sin(angle);
            y = (selfX - origin.x) * std::sin(angle)
                + (y - origin.y) * std::cos(angle);
            return *this;
        }

        double norm() const
        {
            return std::sqrt(dot(*this));
        }

        bool nil() const
        {
            return dot(*this) == 0;
        }

        Vector<T> & normalize()
        {
            return *this /= norm();
        }

        Vector<T> unit() const
        {
            return Vector<T>(*this).normalize();
        }

        float angle(const Vector<T> & v) const
        {
            float angle = std::atan2(v.y, v.x) - std::atan2(y, x);
            if (angle <= 0)
            {
                return angle + 2*M_PI;
            }
            else if (angle < 2*M_PI)
            {
                return angle;
            }
            else
            {
                return 0;
            }
        }

        Vector<T> normal() const
        {
            return Vector<T>(*this).rotate(M_PI_2);
        }

        Vector<T> & operator=(const Vector<T> & v)
        {
            x = v.x;
            y = v.y;
            return *this;
        }

        Vector<T> operator+=(const Vector<T> & v)
        {
            x += v.x;
            y += v.y;
            return *this;
        }

        Vector<T> & operator-=(const Vector<T> & v)
        {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        template <class U>
            Vector<T> & operator/=(U coef)
        {
            T c = static_cast<T>(coef);
            if (c == 0)
            {
                if (coef != 0)
                {
                    if (coef < 0)
                    {
                        x = -std::numeric_limits<T>::infinity();
                        y = -std::numeric_limits<T>::infinity();
                    }
                    else
                    {
                        x = std::numeric_limits<T>::infinity();
                        y = std::numeric_limits<T>::infinity();
                    }
                }
                else
                {
                    throw ZeroDivision();
                }
            }
            else
            {
                x /= c;
                y /= c;
            }
            return *this;
        }

        template <class U>
            Vector<T> & operator*=(U coef)
        {
            T c = static_cast<T>(coef);
            x *= c;
            y *= c;
            return *this;
        }

        template <class U>
            Vector<T> operator*(U coef) const
        {
            return Vector<T>(*this) *= coef;
        }

        template <class U>
            Vector<T> operator/(U coef) const
        {
            return Vector<T>(*this) /= coef;
        }

        Vector<T> operator+(const Vector<T> & v) const
        {
            return Vector<T>(*this) += v;
        }

        Vector<T> operator-(const Vector<T> & v) const
        {
            return Vector<T>(*this) -= v;
        }

        bool operator==(const Vector<T> & v) const
        {
            return x == v.x && y == v.y;
        }

        bool operator!=(const Vector<T> & v) const
        {
            return !(*this == v);
        }
    }; // class Vector
} // namespace Geometry

#endif // VECTOR_H_INCLUDED_
