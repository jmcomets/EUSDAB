#ifndef PHYSICS_TRANSFORM_H_
#define PHYSICS_TRANSFORM_H_

#include <physics/config.h>

namespace EUSDAB
{
    namespace Physics
    {
        class Transform
        {
            public:
                Transform(Transform &&) = delete;
                Transform(Transform const &) = delete;
                Transform operator=(Transform const &) = delete;

                Transform() = default;
                Transform(Vector2 const & pos = Vector2(),
                        Vector2 const & vel = Vector2(),
                        Vector2 const & acc = Vector2());
                ~Transform() = default;

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
