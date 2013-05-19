#include <graphics/controller.h>
#include <cassert>
#include <state.h>
#include <animation.h>

namespace EUSDAB
{
    namespace Graphics
    {
        void Controller::draw()
        {
            // Barycenter of the entities
            Physics::Vector2 barycenter;

            auto drawSpriteAt = [&](sf::Sprite & sp,
                    const Physics::Vector2 & p)
            {
                sp.setPosition(p.x, p.y);
                _target.draw(sp);
            };

            for (Entity * e : _entityList)
            {
                // Check that entity's state is non-nil
                State * s = e->state();
                assert(s != nullptr);

                // Check that state's animation is non-nil
                Animation * a = s->animation();
                if (a == nullptr) { continue; }

                // All is ok, draw animation's sprite
                drawSpriteAt(a->sprite(), e->position());
            }

            for (Entity * e : _playerList)
            {
                // Check that entity's state is non-nil
                State * s = e->state();
                assert(s != nullptr);

                // Check that state's animation is non-nil
                Animation * a = s->animation();
                if (a == nullptr) { continue; }

                // All is ok, draw animation's sprite
                const Physics::Vector2 & p = e->position();
                drawSpriteAt(a->sprite(), p);

                // Add position vector to barycenter
                barycenter += p;
            }

            // Convert to barycenter by dividing by number of entities
            barycenter /= static_cast<Physics::Unit>(_playerList.size());
            sf::Vector2f sfBarycenter(barycenter.x, barycenter.y);
            sf::View view = _target.getView();
            view.move(sfBarycenter - view.getCenter());

            // Zoom camera
            //Camera::ZPF factor = 1.f;
            //view.zoom(factor);

            // Set final view
            _target.setView(view);
        }

        void Controller::addEntity(Entity * entity)
        {
            assert(entity != nullptr);
            assert(_playerList.find(entity) != _playerList.end());
            _entityList.insert(entity);
        }

        void Controller::removeEntity(Entity * entity)
        {
            _entityList.erase(entity);
        }
    }
}
