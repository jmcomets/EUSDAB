#ifndef OBB2_H_
#define OBB2_H_

#include <cmath>
//#include <physics/vector2.h>
//#include <utils/interval.h>
#include <vector2.h>
#include <interval.h>



#ifndef RELEASE
#  include <SFML/Graphics/RenderTarget.hpp>
#  include <SFML/Graphics.hpp>
#  include <SFML/Graphics/RectangleShape.hpp>
#endif

namespace EUSDAB
{
    namespace Physics
    {
        template <typename T>
            class OBB2
            {
                public:
                    typedef double AngleUnit;

                    OBB2() :
                        _w(0), _h(0), _center(0, 0), _angle(0), _X(0, 0), _Y(0, 0)
                {
                }

                    OBB2(T w, T h, Vector2<T> center, AngleUnit angle):
                        _w(w), _h(h), _center(center), _angle(angle),
                        _X(Vector2<T>(1, 0).rotate(angle) * w / static_cast<T>(2)),
                        _Y(Vector2<T>(0, 1).rotate(angle) * h / static_cast<T>(2))
                {
                }

                    OBB2(OBB2 &&) = default;
                    OBB2(OBB2 const &) = default;
                    ~OBB2() = default;
                    OBB2 & operator=(OBB2 const &) = default;

                    template <typename U>
                        bool collides(OBB2<U> const & other) const
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
                            return *this;
                        }

                    AngleUnit angle() const
                    {
                        return _angle;
                    }

                    Vector2<T> const & center() const
                    {
                        return _center;
                    }

                    Vector2<T> const & X() const
                    {
                        return _X;
                    }

                    Vector2<T> const & Y() const
                    {
                        return _Y;
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
#endif

                protected:
                    bool overlaps1Way(OBB2 const & other) const
                    {
                        typedef Utils::Interval<T> Interval;
                        Vector2<T> xAxis(_X.unit());
                        Vector2<T> yAxis(_Y.unit());
                        Vector2<T> obblxAxis(other._X.unit());
                        Vector2<T> obblyAxis(other._Y.unit());
                        Vector2<T> extent(_X + _Y);
                        Vector2<T> obbExtent(other._X + other._Y);
                        Vector2<T> lExtent(_center - extent);
                        Vector2<T> rExtent(_center + extent);
                        Vector2<T> obblExtent(other._center - obbExtent);
                        Vector2<T> obbrExtent(other._center + obbExtent);

#ifndef RELEASE
                        std::cout << "overlaps1Way:" << std::endl
                            << "\tlExtent = " << lExtent << std::endl
                            << "\trExtent = " << rExtent << std::endl
                            << "\tobblExtent = " << obblExtent << std::endl
                            << "\tobbrExtent = " << obbrExtent << std::endl
                            << "\t X = " << _X << std::endl
                            << "\t Y = " << _Y << std::endl;
#endif

                        Vector2<T> myXOnOther = _X;
                        myXOnOther.rotate(other._angle, other._X);
                        Vector2<T> myYOnOther = _Y;
                        myYOnOther.rotate(other._angle, other._Y);
                        if(!(
                                Interval(myXOnOther.x(), myXOnOther.x() + myXOnOther.norm()).intersects
                                (Interval(other._X.x(), other._X.x() + other._X.norm()))
                                &&
                                Interval(myYOnOther.y(), myXOnOther.y() + myYOnOther.norm()).intersects
                                (Interval(other._Y.y(), other._Y.y() + other._Y.norm()))
                            ))
                            return false;

                        Vector2<T> otherXOnMe = other._X;
                        otherXOnMe.rotate(_angle, _X);
                        Vector2<T> otherYOnMe = other._Y;
                        otherYOnMe.rotate(_angle, _Y);
                        if(!(
                                Interval(otherXOnMe.x(), otherXOnMe.x() + otherXOnMe.norm()).intersects
                                (Interval(_X.x(), _X.x() + _X.norm()))
                                &&
                                Interval(otherYOnMe.y(), otherYOnMe.y() + otherYOnMe.norm()).intersects
                                (Interval(_Y.y(), _Y.y() + _Y.norm()))
                            ))
                            return false;

                        return true;

                        return (Interval(lExtent.dot(xAxis), rExtent.dot(xAxis)).
                            intersects
                            (Interval(obblExtent.dot(xAxis), obbrExtent.dot(xAxis)))
                            &&
                            Interval(lExtent.dot(yAxis), rExtent.dot(yAxis)).
                            intersects
                            (Interval(obblExtent.dot(yAxis), obbrExtent.dot(yAxis))))
                            &&
                            (Interval(lExtent.dot(obblxAxis), rExtent.dot(obblxAxis)).
                            intersects
                            (Interval(obblExtent.dot(obblxAxis), obbrExtent.dot(obblxAxis)))
                            &&
                            Interval(lExtent.dot(obblyAxis), rExtent.dot(obblyAxis)).
                            intersects
                            (Interval(obblExtent.dot(obblyAxis), obbrExtent.dot(obblyAxis))));
                    }

                private:
                    T _w, _h;
                    AngleUnit _angle;
                    Vector2<T> _X, _Y;
                    Vector2<T> _center;
            };
    }
}

#endif //OBB2
