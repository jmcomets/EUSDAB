#include <graphics/controller.h>
#include <state.h>
#include <animation.h>
#include <SFML/Graphics.hpp>

namespace EUSDAB
{
    namespace Graphics
    {
        void Controller::draw()
        {
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

            // Barycenter of the entities
            Physics::Vector2 barycenter;

            // Bounding box
            Physics::AABB bbox;

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

                for (const Physics::Hitbox & hb : a->current().hitboxList())
                {
                    bbox.merge(hb.globalAABB());
                }
            }

            // Convert to barycenter by dividing by number of entities
            barycenter /= static_cast<Physics::Unit>(_playerList.size());
            sf::Vector2f sfBarycenter(barycenter.x, barycenter.y);
            sf::View view = _target.getView();
            view.move(sfBarycenter - view.getCenter());

            sf::Vector2f bboxSize(bbox.width(), bbox.height());
            sf::RectangleShape cameraRect(bboxSize);
            cameraRect.setOutlineColor(sf::Color::Yellow);
            cameraRect.setOutlineThickness(1.0f);
            cameraRect.setFillColor(sf::Color::Transparent);
            cameraRect.setOrigin(bboxSize.x / 2.0f, bboxSize.y / 2.0f);
            cameraRect.setPosition(sfBarycenter);
            _target.draw(cameraRect);

            // Zoom camera
            //Camera::ZPF factor = 1.f;

            const sf::Vector2f & viewSize = view.getSize();
            float factor = std::min(viewSize.x / bboxSize.x,
                    viewSize.y / bboxSize.y);
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
