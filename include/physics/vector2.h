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
                    Vector2(T const && __x = T(), T const && __y = T()):
                        _x(__x),
                        _y(__y)
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

                    void x(T const & __x)
                    {
                        _x = __x;
                    }

                    void y(T const & __y)
                    {
                        _y = __y;
                    }

                    bool operator==(Vector2 const & __other)
                    {
                        return _x == __other._x && _y == __other._y;
                    }

                    bool operator!=(Vector2 const & __other)
                    {
                        return !this->operator==(__other);
                    }

                    Vector2 & operator+=(Vector2 const & __other)
                    {
                        _x += __other._x;
                        _y += __other._y;
                        return *this;
                    }

                    Vector2 & operator-=(Vector2 const & __other)
                    {
                        _x -= __other._x;
                        _y -= __other._y;
                       return *this;
                    }

                    Vector2 & operator*=(T const & __scale)
                    {
                        _x *= __scale;
                        _y *= __scale;
                        return *this;
                    }

                    Vector2 & operator/=(T const & __scale)
                    {
                        _x /= __scale;
                        _y /= __scale;
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

                    Vector2 & translate(T const & __tx, T const & __ty)
                    {
                        _x += __tx;
                        _y += __ty;
                        return *this;
                    }

                    Vector2 & translate(Vector2<T> const & __t)
                    {
                        translate(__t._x, __t._y);
                        return *this;
                    }

                private:
                    T _x;
                    T _y;
            };

        template <typename T>
            inline Vector2<T> operator+(Vector2<T> __l, Vector2<T> const & __r)
            {
                return __l += __r;
            }

        template <typename T>
            inline Vector2<T> operator-(Vector2<T> __l, Vector2<T> const & __r)
            {
                return __l -= __r;
            }

        template <typename T>
            inline Vector2<T> operator*(Vector2<T> __l, T const & __r)
            {
                return __l *= __r;
            }

        template <typename T>
            inline Vector2<T> operator/(Vector2<T> __l, T const & __r)
            {
                return __l /= __r;
            }
    }
}

#endif

