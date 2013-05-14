#ifndef WORLD_H_
#define WORLD_H_

#include <physics/config.h>

namespace EUSDAB
{
    namespace Physics
    {
        class World
        {
            public:
                World() = delete;
                World(World &&) = default;
                World(const World &) = default;
                ~World() = default;
                World & operator=(const World &) = default;

                // Construct from world box and gravity vector
                World(const AABB &, const Vector2 &);

                // Return if an Hitbox is (by at least overlapping)
                // contained within the world, using the underlying AABB
                bool contains(const Hitbox &) const;

                // Get underlying AABB
                const AABB & aabb() const;
                // ...non-const version
                AABB & aabb();

                // Get underlying gravity vector
                const Vector2 & gravity() const;
                // ...non-const version
                Vector2 & gravity();

            private:
                Vector2 _gravity;
                AABB _aabb;
        };
    }
}

#endif
