#ifndef PHYSICS_HITBOX_H_
#define PHYSICS_HITBOX_H_

#include <vector>
#include <limits>
#include <physics/aabb.h>

namespace EUSDAB
{
    namespace Physics
    {
        // Hitbox template class handling hitbox semantics,
        //   also "uniquely" identified by it.
        // This means that hitboxA == hitboxB if, and only
        //   if their semantics are the same.
        template <class T>
            class HitboxT
        {
            public:
                // Access corresponding types from within 
                //  class instanciation (don't use extra templates).
                typedef T Unit;
                typedef AABBT<Unit> AABB;
                typedef Vector2T<Unit> Vector2;
                typedef std::vector<AABB> AABBList;

                // Hitbox semantic, type must be minimized
                //   to hold all semantic values (allowing hash).
                typedef unsigned char Semantic_type;
                enum Semantic: Semantic_type
                {
                    Nothing  = 1 << 0,
                    Attack   = 1 << 1,
                    Defense  = 1 << 2,
                    Foot     = 1 << 3,
                    Grab     = 1 << 4,
                    Grabable = 1 << 5
                };

                // Default constructor, setting hitbox semantic
                //  as the "Defense" semantic.
                HitboxT():
                    _sem(Defense),
                    _aabbList(),
                    _aabbGlobal()
                {
                }

                // Value constructor, setting a particular hitbox
                //  semantic instead of the basic "Defense" semantic.
                HitboxT(Semantic sem):
                    _sem(sem),
                    _aabbList(),
                    _aabbGlobal()
                {
                }

                HitboxT(HitboxT<Unit> &&) = default;
                HitboxT(HitboxT<Unit> const &) = default;
                ~HitboxT() = default;
                HitboxT<Unit> & operator=(HitboxT<Unit> const &) = default;

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

                // Allow sorting by semantic for identification
                //  by Semantic (used for BST).
                bool operator<(const HitboxT<Unit> & hb) const
                {
                    return _sem < hb._sem;
                }

                // Add an AABB to the hitbox, resizing the global hitbox
                //   if necessary, no check is done on the relevance of
                //   the added AABB.
                void addAABB(const AABB & aabb)
                {
                    // Add the AABB to the list
                    _aabbList.push_back(aabb);

                    // Merge the global AABB with the added one
                    _aabbGlobal.merge(aabb);
                }

                // Check if collides with another Hitbox
                bool collides(const HitboxT<Unit> & hitbox) const
                {
                    // If the two hitboxes' global AABBs don't collide,
                    //   we know that these hitboxes don't collide either
                    if (hitbox._aabbGlobal.collides(_aabbGlobal) == false)
                    {
                        return false;
                    }

                    // Collision if any two AABBs of each hitbox collide
                    for (const AABB & aabb : _aabbList)
                    {
                        for (const AABB & aabb_other : hitbox._aabbList)
                        {
                            if (aabb.collides(aabb_other))
                            {
                                return true;
                            }
                        }
                    }
                    return false;
                }
                // ...overload for direct check with AABB,
                //   always checks with _aabbGlobal so slower than
                //   with Hitbox for AABB list
                bool collides(const AABB & otherAABB) const
                {
                    if (otherAABB.collides(_aabbGlobal) == false)
                    {
                        return false;
                    }

                    for (const AABB & aabb : _aabbList)
                    {
                        if (otherAABB.collides(aabb))
                        {
                            return true;
                        }
                    }
                    return false;
                }

                // Translate the Hitbox (takes AABB::Unit)
                void translate(typename AABB::Unit const & x, 
                        typename AABB::Unit const & y)
                {
                    _aabbGlobal.translate(x, y);
                    for (AABB & aabb : _aabbList)
                    {
                        aabb.translate(x, y);
                    }
                }
                // ... overload with AABB::Vector2
                void translate(typename AABB::Vector2 const & v)
                {
                    translate(v.x, v.y);
                }

                // Get/Set the Hitbox's semantic
                Semantic semantic() const
                {
                    return _sem;
                }
                void setSemantic(Semantic sem)
                {
                    _sem = sem;
                }

                // Expose the inner AABB list, but don't allow
                //  modification by external actors.
                const AABBList & aabbList() const
                {
                    return _aabbList;
                }

                // Expose the inner global AABB, but don't allow
                //  modification by external actors.
                const AABB & globalAABB() const
                {
                    return _aabbGlobal;
                }

            private:
                // Hitbox semantic
                Semantic _sem;

                // List of all actual (~small) AABBs
                AABBList _aabbList;

                // Global AABB englobing all smaller ones,
                //   simple performance enhancement
                AABB _aabbGlobal;
        };
    }
}

// Specialization of std::hash<EUSDAB::Physics::Hitbox<T>>,
// for any type T.
#include <functional>

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
