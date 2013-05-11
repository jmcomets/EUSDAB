#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <set>
#include <SFML/Graphics/RenderTarget.hpp>
#include <entity.h>

namespace EUSDAB
{
    namespace Graphics
    {
        class Controller
        {
            public:
                Controller() = delete;
                Controller(Controller &&) = default;
                Controller(const Controller &) = default;
                ~Controller() = default;
                Controller & operator=(const Controller &) = default;

                Controller(sf::RenderTarget &);

                // Draw the Controller to its currently set target
                void draw();

                // Add an Entity to the Controller
                void addEntity(Entity * entity);

                // ...range version
                template <typename InputIter>
                    void addEntity(InputIter begin, InputIter end)
                {
                    for (; begin != end ; begin++)
                    {
                        addEntity(*begin);
                    }
                }

                // Remove an Entity from the Controller
                void removeEntity(Entity * entity);

            private:
                sf::RenderTarget & _target;
                std::set<Entity *> _entities;
        };
    }
}

#endif
