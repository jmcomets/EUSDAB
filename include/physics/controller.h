#ifndef PHYSICS_CONTROLLER_H_
#define PHYSICS_CONTROLLER_H_

#include <vector>
#include <entity.h>
#include <input/controller.h>
#include <physics/config.h>
#include <physics/world.h>

namespace EUSDAB
{
    namespace Physics
    {
        class Controller
        {
            public:
                Controller() = delete;
                Controller(Controller &&) = default;
                Controller(const Controller &) = delete;
                Controller & operator=(Controller const &) = delete;

                // Pass Input Controller when constructing, allowing
                // the Physics Controller to send input signals
                // to all its handled entities
                Controller(Input::Controller &, World *);

                // Delete world along with Controller
                ~Controller();

                // Add an Entity to the controller
                void addEntity(Entity *);
                // ... range version
                template <typename InputIter>
                    void addEntity(InputIter begin, InputIter end)
                {
                    for (; begin != end; begin++)
                    {
                        addEntity(*begin);
                    }
                }

                // Update collision and send signals to entity
                // Must be called only once per frame
                void update();

            protected:
                // Collision of two entities
                void handleEntityCollision(Entity *, Entity *);

                // Life of entities in world
                void handleWorldEntity(Entity *);

                // Update entities' transformation
                void handleEntityTransform(Entity * e);

                // Update entities' movement
                void handleEntityMovement(Entity * e);

            private:
                // Input Controller
                Input::Controller & _input;

                // Physics world
                World * _world;

                // Reference to Entities
                std::vector<Entity *> _entityList;
        };
    }
}

#endif
