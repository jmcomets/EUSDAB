#ifndef PHYSICS_CONFIG_H_
#define PHYSICS_CONFIG_H_

#include <physics/vector2.h>
#include <physics/aabb.h>
#include <physics/hitbox.h>

namespace EUSDAB
{
    namespace Physics
    {
        typedef int Unit;
        typedef Vector2T<Unit> Vector2;
        typedef AABBT<Unit> AABB;
        typedef HitboxT<Unit> Hitbox;
    }
}

#endif
