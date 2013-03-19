#include <physics/hitbox.h>
#include <algorithm>

namespace EUSDAB
{
    namespace Physics
    {
        // Delegate to STL's `initializer_list` constructor
        Hitbox::Hitbox(std::initializer_list<OBB2<Unit>> il):
            _obbList(il)
        {
        }

        // Single OBB addition -> basic `push_back`
        Hitbox & Hitbox::add(const OBB2<Unit> & obb)
        {
            _obbList.push_back(obb);
            return *this;
        }

        // Multiple OBB addition -> STL's `copy` algorithm (for specific 
        //   performance enhancements)
        Hitbox & Hitbox::add(const Hitbox & hitbox)
        {
            std::copy(hitbox._obbList.begin(), hitbox._obbList.end(), 
                    _obbList.end());
            return *this;
        }

        // Any of our OBBs collides with given one -> collision
        bool Hitbox::collides(const OBB2<Unit> & obb) const
        {
            for (auto myObb : _obbList)
            {
                if (myObb.collides(obb))
                {
                    return true;
                }
            }
            return false;
        }

        // Any of the other Hitbox's OBBs collides with us -> Collision
        bool Hitbox::collides(const Hitbox & hitbox) const
        {
            for (auto obb : hitbox._obbList)
            {
                if (collides(obb))
                {
                    return true;
                }
            }
            return false;
        }

        // Any of our OBBs contain given vector -> Contained
        bool Hitbox::contains(const Vector2<Unit> & v) const
        {
            for (const OBB2<Unit> & obb : _obbList)
            {
                if (obb.contains(v))
                {
                    return true;
                }
            }
            return false;
        }

        // Rotate -> all of our OBBs
        Hitbox & Hitbox::rotate(Unit angle)
        {
            for (auto obb : _obbList)
            {
                obb.rotate(angle);
            }
            return *this;
        }

        // Translate -> all of our OBBs
        Hitbox & Hitbox::translate(const Vector2<Unit> & v)
        {
            for (auto obb : _obbList)
            {
                obb.translate(v);
            }
            return *this;
        }
    }
}
