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
            class HitboxT
        {
            public:
                // Access corresponding types from within 
                //  class instanciation (don't use extra templates).
                typedef T Unit;
                typedef AABBT<Unit> AABB;

                // Hitbox semantic (explicit...)
                enum Semantic: unsigned char
                {
                    Attack   = 1 << 0,
                    Defense  = 1 << 1,
                    Foot     = 1 << 2,
                    Grab     = 1 << 3,
                    Grabable = 1 << 4
                };

                HitboxT(Semantic semantic = Defense):
                    _sem(semantic),
                    _aabbList(),
                    _aabbGlobal(0, 0, 0, 0)
                {
                }

                HitboxT(HitboxT &&) = default;
                HitboxT(HitboxT const &) = default;
                ~HitboxT() = default;
                HitboxT & operator=(HitboxT const &) = default;

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
                bool operator==(const HitboxT<Unit> & hb) const
                {
                    return *this == hb._sem;
                }

                // Allow sorting
                bool operator<(const HitboxT<Unit> & hb) const
                {
                    return _sem < hb._sem;
                }

                // Add an AABBT to the hitbox, resizing the global hitbox
                //   if necessary, no check is done on the relevance of
                //   the added AABBT.
                void addAABB(AABB const & aabb)
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
                        _aabbGlobal = AABB(0, 0, 0, 0);
                    }
                    else
                    {
                        Unit minX = _aabbList[0].x();
                        Unit maxX = _aabbList[0].x() + _aabbList[0].width();
                        Unit minY = _aabbList[0].y();
                        Unit maxY = _aabbList[0].y() + _aabbList[0].height();

                        for (AABB & aabb : _aabbList)
                        {
                            minX = std::min(minX, aabb.x());
                            maxX = std::max(maxX, aabb.x() + aabb.width());
                            minY = std::min(minY, aabb.y());
                            maxY = std::max(maxY, aabb.y() + aabb.height());
                        }

                        _aabbGlobal = AABB(minX, minY, maxX - minX, maxY - minY);
                    }
                }

                bool collides(HitboxT const & other) const
                {
                    if (!other._aabbGlobal.collides(_aabbGlobal))
                    {
                        return false;
                    }

                    for (AABB const & aabb : _aabbList)
                    {
                        for(AABB const & aabb_other : other._aabbList)
                        {
                            if(aabb.collides(aabb_other))
                            {
                                return true;
                            }
                        }
                    }
                    return false;
                }

                void translate(Unit const & x, Unit const & y)
                {
                    _aabbGlobal.translate(x, y);
                    for (AABB & aabb : _aabbList)
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
                std::vector<AABB> _aabbList;
                AABB _aabbGlobal;
        };
    }
}

namespace std
{
    template <>
        template <class T> struct hash<EUSDAB::Physics::HitboxT<T>>
    {
        size_t operator()(const EUSDAB::Physics::HitboxT<T> & x) const
        {
            typedef typename EUSDAB::Physics::HitboxT<T>::Semantic Semantic;
            return std::hash<Semantic>(x.semantic());
        }
    };
}

#endif
