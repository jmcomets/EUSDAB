#ifndef PHYSICS_CONTROLLER_H_
#define PHYSICS_CONTROLLER_H_

namespace EUSDAB
{
    namespace Input
    {
        class Controller;
    }

    namespace Physics
    {
        class Controller
        {
            public:
                Controller(Controller &&) = default;
                Controller(Controller const &) = delete;
                Controller & operator=(Controller const &) = delete;

                Controller(Input::Controller &);
                ~Controller();

                // Add an entity to the controller
                void addEntity(Entity *);

                // Update collision and send signals to entity
                // Must be called only once per frame
                void update();

            protected:
                Input::Controller & _input_controller;
                std::vector<Entity *> _entity_list;
        };
    }
}

#endif

