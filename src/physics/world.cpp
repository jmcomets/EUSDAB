#include <physics/world.h>

namespace EUSDAB
{
    namespace Physics
    {
        World::World(const AABB & aabb,
                const Vector2 & gravity):
            _gravity(gravity),
            _aabb(aabb)
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

        const Vector2 & World::gravity() const
        {
            return _gravity;
        }

        Vector2 & World::gravity()
        {
            return _gravity;
        }
    }
}
