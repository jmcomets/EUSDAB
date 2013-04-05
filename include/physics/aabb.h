#ifndef PHYSICS_AABB_H_
#define PHYSICS_AABB_H_

#ifdef SFML_TEST
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#endif

namespace EUSDAB
{
    namespace Physics
    {
        template <typename T>
#ifdef SFML_TEST
            class AABB : public sf::Drawable
#else
            class AABB
#endif
            {
                public:
                    AABB(T const & __x, T const & __y, T const & __w, T const & __h):
                        _x(__x),
                        _y(__y),
                        _w(__w),
                        _h(__h)
                    {
#ifdef SFML_TEST
                        _sfml_rect = sf::RectangleShape(sf::Vector2f(static_cast<float>(_w), static_cast<float>(_h)));
#endif
                    }

                    AABB(AABB const &) = default;
                    AABB(AABB &&) = default;

                    AABB & operator=(AABB const &) = default;

                    ~AABB() = default;

                    T const & x() const
                    {
                        return _x;
                    }

                    T const & y() const
                    {
                        return _y;
                    }

                    T const & w() const
                    {
                        return _w;
                    }

                    T const & h() const
                    {
                        return _h;
                    }

                    void x(T const & __x)
                    {
                        _x = __x;
                    }

                    void y(T const & __y)
                    {
                        _y = __y;
                    }

                    void w(T const & __w)
                    {
                        _w = __w;
                    }

                    void h(T const & __h)
                    {
                        _h = __h;
                    }

                    bool collide(AABB<T> const & __other) const
                    {
                        if((_x >= __other._x + __other._w)
                                || (_x + _w <= __other._x)
                                || (_y >= __other._y + __other._h)
                                || (_y + _h <= __other._y))
                            return false;
                        return true;
                    }

                    void translate(T const & __tx, T const & __ty)
                    {
                        _x += __tx;
                        _y += __ty;
                    }

#ifdef SFML_TEST
                public:
                    void color(sf::Color const & __color)
                    {
                        _sfml_rect.setFillColor(__color);
                    }

                    void draw(sf::RenderTarget & __target, sf::RenderStates __state) const
                    {
                        __state.transform.translate(_x, _y);
                        __target.draw(_sfml_rect, __state);
                    }

                protected:
                    sf::RectangleShape _sfml_rect;
#endif

                private:
                    T _x;
                    T _y;
                    T _w;
                    T _h;
            };
    }
}

#endif

