#include <graphics/controller.h>
#include <state.h>
#include <animation.h>
#include <SFML/Graphics.hpp>
#include <map.h>

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

            // Bounding box
            Physics::AABB bbox;

            auto doHitbox = [&] (Physics::Hitbox hb, Physics::Vector2 const & p)
            {
                hb.translate(p);

                Physics::Hitbox::Semantic_type sem = hb.semantic();
                sf::Color color;
                switch (sem)
                {
                    case Physics::Hitbox::Semantic::Attack   :
                        color = sf::Color::Red; break;

                    case Physics::Hitbox::Semantic::Defense  :
                        color = sf::Color::Yellow; break;

                    case Physics::Hitbox::Semantic::Foot     :
                        color = sf::Color::Green; break;

                    case Physics::Hitbox::Semantic::Grab     :
                        color = sf::Color::Blue; break;

                    case Physics::Hitbox::Semantic::Grabable :
                        color = sf::Color::Magenta; break;

                    case Physics::Hitbox::Semantic::Collision :
                        color = sf::Color::Cyan; break;

                    default: break;
                }


                for (Physics::AABB aabb : hb.aabbList())
                {
                    sf::Vector2f size(aabb.width(), aabb.height());
                    sf::RectangleShape rect(size);
                    rect.setOrigin(size.x / 2.0f, size.y / 2.0f);
                    rect.setPosition(aabb.x(), aabb.y());
                    rect.setOutlineColor(color);
                    rect.setOutlineThickness(1.0f);
                    rect.setFillColor(sf::Color::Transparent);
                    _target.draw(rect);
                }
            };

            auto doHitboxes = [&] (Animation * a, const Physics::Vector2 & p)
            {
                for (Physics::Hitbox hb : a->current().hitboxList())
                {
                    bbox.merge(hb.globalAABB());
                    doHitbox(hb, p);
                }
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
                auto p = e->position();
                drawSpriteAt(a->sprite(), p);
                doHitboxes(a, p);
                doHitbox(e->hitbox(), p);
                Map * map = dynamic_cast<Map *>(e);
                if (map == nullptr)
                { 
                    std::cerr << "map " << e << " is null" << std::endl;
                    continue;
                }

                for (sf::Sprite & s : map->getSprites())
                {
                    _target.draw(s);
                }
            }

            // Barycenter of the entities
            Physics::Vector2 barycenter;

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

                doHitboxes(a, p);
                doHitbox(e->hitbox(), p);
            }

            // Convert to barycenter by dividing by number of entities
            barycenter /= static_cast<Physics::Unit>(_playerList.size());
            sf::Vector2f sfBarycenter(barycenter.x, barycenter.y);
            sf::View view = _target.getView();
            view.move(sfBarycenter - view.getCenter());

            sf::Vector2f bboxSize(bbox.width(), bbox.height());
            //sf::RectangleShape cameraRect(bboxSize);
            //cameraRect.setOutlineColor(sf::Color::Yellow);
            //cameraRect.setOutlineThickness(1.0f);
            //cameraRect.setFillColor(sf::Color::Transparent);
            //cameraRect.setOrigin(bboxSize.x / 2.0f, bboxSize.y / 2.0f);
            //cameraRect.setPosition(sfBarycenter);
            //_target.draw(cameraRect);

            // Zoom camera
            bboxSize += sf::Vector2f(50, 50);
            const sf::Vector2f & viewSize = view.getSize();
            view.zoom(std::max(bboxSize.x / viewSize.x,
                        bboxSize.y / viewSize.y));

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
