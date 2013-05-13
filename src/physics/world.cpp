#include <physics/world.h>

namespace EUSDAB
{
    namespace Physics
    {
        World::World(const Unit & x, const Unit & y,
                const Unit & w, const Unit & h):
            _aabb(x, y, w, h)
        {
        }

        World::World(const Vector2 & pos,
                const Unit & w, const Unit & h):
            _aabb(pos, w, h)
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
