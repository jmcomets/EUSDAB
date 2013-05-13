#include <graphics/controller.h>
#include <state.h>
#include <animation.h>

namespace EUSDAB
{
    namespace Graphics
    {
        Controller::Controller(sf::RenderTarget & target):
            _target(target), _entities()
        {
        }

        void Controller::draw()
        {
            for (auto e : _entities)
            {
                _target.draw(e->state()->animation()->sprite());
            }
        }

        void Controller::addEntity(Entity * entity)
        {
            _entities.insert(entity);
        }

        void Controller::removeEntity(Entity * entity)
        {
            _entities.erase(entity);
        }
    }
}
