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
            // Barycenter of the entities
            Physics::Vector2 barycenter;

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

                // Add position vector to barycenter
                barycenter += p;
            }

            // Convert to barycenter by dividing by number of entities
            barycenter /= _entities.size();
            sf::Vector2f sfBarycenter(barycenter.x(), barycenter.y());
            sf::View view = _target.getView();
            view.move(sfBarycenter - view.getCenter());
            _target.setView(view);
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
