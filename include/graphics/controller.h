#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <array>
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

                // Camera structure, used for view
                //  on Controller's entities
                struct Camera
                {
                    // Dimension type
                    typedef float Size;

                    // Zoom-Per-Frame type
                    typedef float ZPF;

                    // Minimum/Maximum zoom dimensions (width, height),
                    //  must be positive values
                    std::array<Size, 2> min, max;

                    // Zoom-Per-Frame amount,
                    //  must be in (0, 1) open interval
                    ZPF zpf;
                } camera;

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
                struct Deeper
                {
                    bool operator()(Entity * lhs, Entity * rhs) const
                    {
                        return lhs->zIndex() < rhs->zIndex();
                    }
                };
                sf::RenderTarget & _target;
                //std::set<Entity *> _entities;
                std::multiset<Entity *, Deeper> _entities;
        };
    }
}

#endif
