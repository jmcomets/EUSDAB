#ifndef PHYSICS_CONTROLLER_H_
#define PHYSICS_CONTROLLER_H_

#include <vector>
#include <entity.h>
#include <input/controller.h>
#include <physics/config.h>

namespace EUSDAB
{
    namespace Physics
    {
        class Controller
        {
            public:
                Controller(Controller &&) = default;
                Controller(Controller const &) = delete;
                ~Controller() = default;
                Controller & operator=(Controller const &) = delete;

                Controller(Input::Controller &);

                // Add an entity to the controller
                void addEntity(Entity *);

                // Update collision and send signals to entity
                // Must be called only once per frame
                void update();

            protected:
                void handleEntityCollision(Entity *, Entity *);

            private:
                Input::Controller & _input;
                std::vector<Entity *> _entityList;
        };
    }
}

#endif

