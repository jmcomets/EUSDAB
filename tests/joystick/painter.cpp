#include "painter.h"
//#include <painter.h>
#include <state.h>
#include <animation.h>

namespace EUSDAB
{
    namespace Graphics
    {
        Painter::Painter(sf::RenderTarget & target):
            _target(target), _entities()
        {
        }

        void Painter::draw()
        {
            for (auto e : _entities)
            {
                _target.draw(e->state()->animation()->sprite());
            }
        }

        void Painter::addEntity(Entity * entity)
        {
            _entities.insert(entity);
        }

        void Painter::removeEntity(Entity * entity)
        {
            _entities.erase(entity);
        }
    }
}
