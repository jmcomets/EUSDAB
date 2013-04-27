#ifndef PHYSICS_HITBOX_H_
#define PHYSICS_HITBOX_H_

#include <vector>
#include <physics/aabb.h>

namespace EUSDAB
{
    namespace Physics
    {
        template <class T>
            class Hitbox
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

                Hitbox(Semantic semantic = Defense):
                    _sem(semantic),
                    _aabbList(),
                    _aabbGlobal(0, 0, 0, 0)
                {
                }

                Hitbox(Hitbox &&) = default;
                Hitbox(Hitbox const &) = default;
                ~Hitbox() = default;
                Hitbox & operator=(Hitbox const &) = default;

                // Return if a hitbox has the asked semantic
                bool isOfSemantic(Semantic sem) const
                {
                    return _sem == sem;
                }
                // ...shortcut operator
                bool operator==(Semantic sem) const
                {
                    return isOfSemantic(sem);
                }

                // Add an AABB to the hitbox, resizing the global hitbox
                //   if necessary, no check is done on the relevance of
                //   the added AABB.
                void addAABB(AABB<T> const & aabb)
                {
                    _aabbList.push_back(aabb);

                    if (_aabbGlobal.x() == 0 && _aabbGlobal.y() == 0 
                            && _aabbGlobal.w() == 0 && _aabbGlobal.h() == 0)
                    {
                        _aabbGlobal.x(aabb.x());
                        _aabbGlobal.y(aabb.y());
                        _aabbGlobal.w(aabb.w());
                        _aabbGlobal.h(aabb.h());
                    }
                    else
                    {
                        if (aabb.x() < _aabbGlobal.x())
                        {
                            _aabbGlobal.w(_aabbGlobal.x() - aabb.x() + _aabbGlobal.w());
                            _aabbGlobal.x(aabb.x());
                        }

                        if (aabb.y() < _aabbGlobal.y())
                        {
                            _aabbGlobal.h(_aabbGlobal.y() - aabb.y() + _aabbGlobal.h());
                            _aabbGlobal.y(aabb.y());
                        }

                        if (aabb.x() + aabb.w() > _aabbGlobal.x() + _aabbGlobal.w())
                        {
                            _aabbGlobal.w(aabb.x() + aabb.w() - _aabbGlobal.x());
                        }

                        if (aabb.y() + aabb.h() > _aabbGlobal.y() + _aabbGlobal.h())
                        {
                            _aabbGlobal.h(aabb.y() + aabb.h() - _aabbGlobal.y());
                        }
                    }
                }

                void do_global()
                {
                    if (_aabbList.size() == 0)
                    {
                        _aabbGlobal = AABB<T>(0, 0, 0, 0);
                    }
                    else
                    {
                        T minX = _aabbList[0].x();
                        T maxX = _aabbList[0].x() + _aabbList[0].width();
                        T minY = _aabbList[0].y();
                        T maxY = _aabbList[0].y() + _aabbList[0].height();

                        for (AABB<T> & aabb : _aabbList)
                        {
                            minX = std::min(minX, aabb.x());
                            maxX = std::max(maxX, aabb.x() + aabb.width());
                            minY = std::min(minY, aabb.y());
                            maxY = std::max(maxY, aabb.y() + aabb.height());
                        }

                        _aabbGlobal = AABB<T>(minX, minY, maxX - minX, maxY - minY);
                    }
                }

                bool collides(Hitbox const & other) const
                {
                    // TODO: Gestion de la sémentique dans les collision
                    // Exemple de regle de sémentique :
                    // Attack & Defense
                    // Grab & Grabable
                    // Foot & Defense

                    if (!other._aabbGlobal.collides(_aabbGlobal))
                    {
                        return false;
                    }

                    for (AABB<T> const & aabb : _aabbList)
                    {
                        for(AABB<T> const & aabb_other : other._aabbList)
                        {
                            if(aabb.collides(aabb_other))
                            {
                                return true;
                            }
                        }
                    }
                    return false;
                }

                void translate(T const & x, T const & y)
                {
                    _aabbGlobal.translate(x, y);
                    for (AABB<T> & aabb : _aabbList)
                    {
                        aabb.translate(x, y);
                    }
                }

            private:
                Semantic _sem;
                std::vector<AABB<T>> _aabbList;
                AABB<T> _aabbGlobal;
        };
    }
}

#endif
