#include <state.h>
#include "painter.h"

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
                e->state()->animation()->advance();
                e->state()->animation()->sprite().setPosition(100, 25);
                _window.draw(e->state()->animation()->sprite());
            }
        }

        void Painter::addEntity(Entity * entity)
        {
            _entities.emplace_back(entity);
        }

        void Painter::removeEntity(Entity * entity)
        {
            for(auto it = _entities.begin(); it != _entities.end(); ++it)
            {
                if((*it) == entity)
                {
                    _entities.erase(it);
                    break;
                }
            }
        }
    }
}
