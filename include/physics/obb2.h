#ifndef OBB2_H_
#define OBB2_H_

#include <cmath>

#include "vector2.h"
#include "interval.h"

#ifndef RELEASE
#  include <SFML/Graphics/RenderTarget.hpp>
#  include <SFML/Graphics.hpp>
#  include <SFML/Graphics/RectangleShape.hpp>
#endif


namespace Geometry
{
    template <typename T>
    class OBB2
    {
        typedef double AngleUnit;

        public:

            OBB2() :
                _w(0), _h(0), _center(0, 0), _angle(0), _X(0, 0), _Y(0, 0)
            {
            }

            OBB2(T w, T h, Vector2<T> center, AngleUnit angle):
                _w(w), _h(h), _center(center), _angle(angle),
                _X(Vector2<T>(1, 0).rotate(angle) * w),
                _Y(Vector2<T>(0, 1).rotate(angle) * h)
            {
            }

            OBB2(OBB2 &&) = default;
            OBB2(OBB2 const &) = default;
            ~OBB2() = default;
            OBB2 & operator=(OBB2 const &) = default;

            template <typename U>
            bool collides(OBB2<U> const & other)
            {
                return overlaps1Way(other) && other.overlaps1Way(*this);
            }

            template <typename U>
            OBB2 & translate(U x, U y)
            {
                Vector2<U> v(x, y);
                _center.translate(v);
                return *this;
            }

            template <typename U>
            OBB2 & translate(Vector2<U> const & v)
            {
                _center.translate(v);
                return *this;
            }

            template <typename U>
            OBB2 & translate(Vector2<U> && v)
            {
                _center.translate(v);
                return *this;
            }

            template <typename U>
            OBB2 & rotate(U const & angle, Vector2<T> const & rel_origin = Vector2<T>())
            {
                _center.rotate(angle, _center + rel_origin);
                _X.rotate(angle);
                _Y.rotate(angle);
                _angle += angle;
                // TODO remove these
                {
                    _w = _X.norm();
                    _h = _Y.norm();
                }
                return *this;
            }

            AngleUnit angle() const
            {
                return _angle;
            }

            Vector2<T> const & center()
            {
                return _center;
            }

#ifndef RELEASE
            typedef sf::RenderTarget Target;
            typedef sf::RenderStates RenderStates;

            OBB2 & render(Target & target, RenderStates rs = RenderStates::Default)
            {
                sf::RectangleShape _shape(sf::Vector2f(_w, _h));
                _shape.setFillColor(color);
                sf::CircleShape _c(1);
                _c.setFillColor(sf::Color::Blue);
                _shape.setPosition(_center.x(), _center.y());
                _shape.setOrigin(_w / 2., _h / 2.);
                _shape.setRotation(-180. * _angle / M_PI);
                _c.setPosition(_center.x(), _center.y());
                target.draw(_shape, rs);
                target.draw(_c, rs);
                return *this;
            }

            sf::Color color;

#endif //RELEASE

        protected:

            bool overlaps1Way(OBB2 const & other) const
            {
                Vector2<T> xAxis(_X.unit());
                Vector2<T> yAxis(_Y.unit());
                Vector2<T> extent(_X + _Y);
                Vector2<T> obbExtent(other._X + other._Y);
                Vector2<T> lExtent(_center - extent / 2);
                Vector2<T> rExtent(_center + extent / 2);
                Vector2<T> obblExtent(other._center - obbExtent / 2);
                Vector2<T> obbrExtent(other._center + obbExtent / 2);

                return Interval<T>(lExtent.dot(xAxis), rExtent.dot(xAxis)).
                    intersects
                    (Interval<T>(obblExtent.dot(xAxis), obbrExtent.dot(xAxis)))
                    &&
                    Interval<T>(lExtent.dot(yAxis), rExtent.dot(yAxis)).
                    intersects
                    (Interval<T>(obblExtent.dot(yAxis), obbrExtent.dot(yAxis)));
            }

        public :
            T _w, _h;
            AngleUnit _angle;
            Vector2<T> _X, _Y;
            Vector2<T> _center;
    };
}

#endif //OBB2

