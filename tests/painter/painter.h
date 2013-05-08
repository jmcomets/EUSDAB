#ifndef PAINTER_H_
#define PAINTER_H_

#include <application.h>
#include <entity.h>
#include <vector>

namespace EUSDAB
{
    namespace Graphics
    {
        class Painter
        {
            public:
                Painter() = delete;
                Painter(Painter &&) = delete;
                Painter(const Painter &) = delete;
                Painter & operator=(const Painter &) = delete;

                Painter(sf::RenderWindow &);
                ~Painter();

                void draw();
                void addEntity(Entity * entity);

            private:
                sf::RenderWindow & _window;
                std::vector<Entity *> _entities;
        };
    }
}

#endif
