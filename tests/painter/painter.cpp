#include <iostream>
#include "painter.h"
#include <state.h>

namespace EUSDAB
{
    namespace Graphics
    {
        Painter::Painter(sf::RenderWindow & window) : _window(window),
            _entities()
        {
        }
        Painter::~Painter()
        {
        }

        void Painter::draw()
        {
            for(auto e : _entities)
            {
                _window.draw(e->state()->animation()->sprite());
                std::cout << e->name() << std::endl;
            }
        }

        void Painter::addEntity(Entity * entity)
        {
            _entities.emplace_back(entity);
        }
    }
}
