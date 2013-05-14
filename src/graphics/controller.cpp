#include <graphics/controller.h>
#include <cassert>
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
                // Check that entity's state is non-nil
                State * s = e->state();
                if (s == nullptr) { continue; }

                // Check that state's animation is non-nil
                Animation * a = s->animation();
                if (a == nullptr) { continue; }

                // All is ok, draw animation's sprite
                sf::Sprite & sp = a->sprite();
                const Physics::Vector2 & p = e->position();
                sp.setPosition(p.x(), p.y());
                _target.draw(sp);
            }
        }

        void Controller::addEntity(Entity * entity)
        {
            assert(entity != nullptr);
            _entities.insert(entity);
        }

        void Controller::removeEntity(Entity * entity)
        {
            _entities.erase(entity);
        }
    }
}
