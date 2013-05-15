#include <physics/world.h>
#include <algorithm>

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
            if (_aabb.contains(hb.globalAABB()))
            {
                return true;
            }
            else
            {
                return std::any_of(hb.aabbList().begin(), hb.aabbList().end(),
                        [&] (const Hitbox::AABB & aabb)
                    {
                        return _aabb.collides(aabb);
                    });
            }
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
