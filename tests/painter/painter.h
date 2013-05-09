#ifndef PAINTER_H_
#define PAINTER_H_

#include <set>
#include <SFML/Graphics/RenderTarget.hpp>
#include <entity.h>

namespace EUSDAB
{
    namespace Graphics
    {
        class Painter
        {
            public:
                Painter() = delete;
                Painter(Painter &&) = default;
                Painter(const Painter &) = default;
                ~Painter() = default;
                Painter & operator=(const Painter &) = default;

                Painter(sf::RenderTarget &);

                // Draw the Painter to its currently set target
                void draw();

                // Add an Entity to the Painter
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

                // Remove an Entity from the Painter
                void removeEntity(Entity * entity);

            private:
                sf::RenderTarget & _target;
                std::set<Entity *> _entities;
        };
    }
}

#endif
