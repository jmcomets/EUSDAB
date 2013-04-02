#ifndef PHYSICS_HITBOX_H_
#define PHYSICS_HITBOX_H_

#include <vector>

#include <physics/aabb.h>

#ifdef SFML_TEST
#include <SFML/Graphics.hpp>
#endif

namespace EUSDAB
{
    namespace Physics
    {
        template <typename T>
#ifdef SFML_TEST
            class Hitbox : public sf::Drawable
#else
            class Hitbox
#endif
            {
                public:
                    enum Semantic
                    {
                        Defense,
                        Foot,
                        Attack,
                        Grab,
                        Grabable
                    };

                    explicit Hitbox(Hitbox::Semantic __semantic = Hitbox::Defense):
                        _semantic(__semantic),
                        _aabb_list(),
                        _aabb_global(0, 0, 0, 0)
                    {
#ifdef SFML_TEST
                        color(sf::Color::Black);
#endif
                    }

                    explicit Hitbox(Hitbox const &) = default;
                    explicit Hitbox(Hitbox &&) = default;

                    Hitbox & operator=(Hitbox const &) = default;

                    ~Hitbox() = default;

                    void addAABB(AABB<T> const & __aabb)
                    {
                        _aabb_list.push_back(__aabb);

                        if(_aabb_global.x() == 0 && _aabb_global.y() == 0 && _aabb_global.w() == 0 && _aabb_global.h() == 0)
                        {
                            _aabb_global.x(__aabb.x());
                            _aabb_global.y(__aabb.y());
                            _aabb_global.w(__aabb.w());
                            _aabb_global.h(__aabb.h());
                        }
                        else
                        {
                            if(__aabb.x() < _aabb_global.x())
                            {
                                _aabb_global.w(_aabb_global.x() - __aabb.x() + _aabb_global.w());
                                _aabb_global.x(__aabb.x());
                            }

                            if(__aabb.y() < _aabb_global.y())
                            {
                                _aabb_global.h(_aabb_global.y() - __aabb.y() + _aabb_global.h());
                                _aabb_global.y(__aabb.y());
                            }

                            if(__aabb.x() + __aabb.w() > _aabb_global.x() + _aabb_global.w())
                                _aabb_global.w(__aabb.x() + __aabb.w() - _aabb_global.x());

                            if(__aabb.y() + __aabb.h() > _aabb_global.y() + _aabb_global.h())
                                _aabb_global.h(__aabb.y() + __aabb.h() - _aabb_global.y());
                        }
                    }

                    void do_global()
                    {
                        if(_aabb_list.size() == 0)
                            _aabb_global = AABB<T>(0, 0, 0, 0);
                        else
                        {
                            T minX = _aabb_list[0].x();
                            T maxX = _aabb_list[0].x() + _aabb_list[0].w();
                            T minY = _aabb_list[0].y();
                            T maxY = _aabb_list[0].y() + _aabb_list[0].h();

                            for(auto aabb : _aabb_list)
                            {
                                minX = std::min(minX, aabb.x());
                                maxX = std::max(maxX, aabb.x() + aabb.w());
                                minY = std::min(minY, aabb.y());
                                maxY = std::max(maxY, aabb.y() + aabb.h());
                            }

                            _aabb_global = AABB<T>(minX, minY, maxX - minX, maxY - minY);
                        }
                    }

                    bool collide(Hitbox const & __other) const
                    {
                        // TODO: Gestion de la sémentique dans les collision
                        // Exemple de regle de sémentique :
                        // Attack & Defense
                        // Grab & Grabable
                        // Foot & Defense

                        if(!__other._aabb_global.collide(_aabb_global))
                            return false;

                        for(auto aabb : _aabb_list)
                            for(auto aabb_other : __other._aabb_list)
                                if(aabb.collide(aabb_other))
                                return true;

                        return false;
                    }

                    void translate(T const & __tx, T const & __ty)
                    {
                        _aabb_global.translate(__tx, __ty);
                        for(AABB<T> & aabb : _aabb_list)
                            aabb.translate(__tx, __ty);
                    }

#ifdef SFML_TEST
                public:
                    void color(sf::Color const & __color)
                    {
                        for(AABB<T> & aabb : _aabb_list)
                            aabb.color(__color);
                    }

                    void draw(sf::RenderTarget & __target, sf::RenderStates __state) const
                    {
                        for(AABB<T> const & aabb : _aabb_list)
                            aabb.draw(__target, __state);
                        sf::RectangleShape rect(sf::Vector2f(_aabb_global.w(), _aabb_global.h()));
                        rect.setOutlineColor(sf::Color::Black);
                        rect.setFillColor(sf::Color(0, 0, 0, 120));

                        __state.transform.translate(_aabb_global.x(), _aabb_global.y());
                        __target.draw(rect, __state);
                    }
#endif

                protected:
                    Hitbox::Semantic _semantic;
                    std::vector<AABB<T> > _aabb_list;
                    AABB<T> _aabb_global;
            };
    }
}
#endif

