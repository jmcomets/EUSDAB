#ifndef PHYSICS_COMPONENT_H_
#define PHYSICS_COMPONENT_H_

#include <physics/config.h>

namespace EUSDAB
{
    namespace Physics
    {
        class Component
        {
            public:
                Component(Component &&) = delete;
                Component(Component const &) = delete;
                Component operator=(Component const &) = delete;

                Component();
                Component(Vector2 const & pos = Vector2, Vector2 const & vel = Vector2, Vector2 const & acc = Vector2);
                ~Component() = default;

                Vector2 const & position() const;
                Vector2 & position();

                Vector2 const & velocity() const;
                Vector2 & velocity();

                Vector2 const & acceleration() const;
                Vector2 & acceleration();

                void update();

            private:
                Vector2 _pos;
                Vector2 _vel;
                Vector2 _acc;
        };
    }
}

#endif
