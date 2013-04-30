#ifndef PHYSICS_HITBOX_H_
#define PHYSICS_HITBOX_H_

#include <functional>
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
                enum Semantic: unsigned char
                {
                    Attack   = 1 << 0,
                    Defense  = 1 << 1,
                    Foot     = 1 << 2,
                    Grab     = 1 << 3,
                    Grabable = 1 << 4
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
                // ...also for class
                bool operator==(const Hitbox<T> & hb) const
                {
                    return *this == hb._sem;
                }

                // Allow sorting
                bool operator<(const Hitbox<T> & hb) const
                {
                    return _sem < hb._sem;
                }

                // Add an AABB to the hitbox, resizing the global hitbox
                //   if necessary, no check is done on the relevance of
                //   the added AABB.
                void addAABB(AABB<T> const & aabb)
                {
                    _aabbList.push_back(aabb);

                    if (_aabbGlobal.x() == 0 && _aabbGlobal.y() == 0 
                            && _aabbGlobal.width() == 0 && _aabbGlobal.height() == 0)
                    {
                        _aabbGlobal.setX(aabb.x());
                        _aabbGlobal.setY(aabb.y());
                        _aabbGlobal.setWidth(aabb.width());
                        _aabbGlobal.setHeight(aabb.height());
                    }
                    else
                    {
                        if (aabb.x() < _aabbGlobal.x())
                        {
                            _aabbGlobal.setWidth(_aabbGlobal.x() - aabb.x() + _aabbGlobal.width());
                            _aabbGlobal.setX(aabb.x());
                        }

                        if (aabb.y() < _aabbGlobal.y())
                        {
                            _aabbGlobal.setHeight(_aabbGlobal.y() - aabb.y() + _aabbGlobal.height());
                            _aabbGlobal.setY(aabb.y());
                        }

                        if (aabb.x() + aabb.width() > _aabbGlobal.x() + _aabbGlobal.width())
                        {
                            _aabbGlobal.setWidth(aabb.x() + aabb.width() - _aabbGlobal.x());
                        }

                        if (aabb.y() + aabb.height() > _aabbGlobal.y() + _aabbGlobal.height())
                        {
                            _aabbGlobal.setHeight(aabb.y() + aabb.height() - _aabbGlobal.y());
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

                Semantic semantic() const
                {
                    return _sem;
                }

            private:
                Semantic _sem;
                std::vector<AABB<T>> _aabbList;
                AABB<T> _aabbGlobal;
        };
    }
}

namespace std
{
    template <>
        template <class T> struct hash<EUSDAB::Physics::Hitbox<T>>
    {
        size_t operator()(const EUSDAB::Physics::Hitbox<T> & x) const
        {
            typedef typename EUSDAB::Physics::Hitbox<T>::Semantic Semantic;
            return std::hash<Semantic>(x.semantic());
        }
    };
}

#endif
