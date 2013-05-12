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

                // Construct from center (x, y) coordinantes, as well as
                //  width and height of world box.
                World(const Unit &, const Unit &, const Unit &, const Unit &);

                // Construct from center point, as well as
                //  width and height of world box.
                World(const Vector2 &, const Unit & w, const Unit & h);

                // Return a Hitbox's physical state:
                //  delegate to underlying AABB
                bool contains(const Hitbox &) const;

                // Get underlying AABB
                const AABB & aabb() const;
                // ...non-const version
                AABB & aabb();

            private:
                AABB _aabb;
        };
    }
}

#endif
