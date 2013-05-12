#include <physics/world.h>

namespace EUSDAB
{
    namespace Physics
    {
        World::World(const Unit &, const Unit &, const Unit &, const Unit &)
        {
        }

        World::World(const Vector2 &, const Unit & w, const Unit & h)
        {
        }

        bool World::contains(const Hitbox & hb) const
        {
            if (_aabb.contains(hb.globalAABB()) == false)
            {
                return false;
            }

            for (Hitbox::AABB aabb : hb.aabbList())
            {
                if (_aabb.contains(aabb) == false)
                {
                    return false;
                }
            }
            return true;
        }

        const AABB & World::aabb() const
        {
            return _aabb;
        }

        AABB & World::aabb()
        {
            return _aabb;
        }
    }
}
