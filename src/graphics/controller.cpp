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
            static std::time_t time = 0;
            time++;

            _shader_rainbow->setParameter("wave_amplitude", 15, 15);
            _shader_rainbow->setParameter("wave_phase", time / 50.0f);
            _shader_rainbow->setParameter("ratio", ((time % 25) / 25.0f));
            auto drawSpriteAt = [&](sf::Sprite & sp,
                    const Physics::Vector2 & p)
            {
                sp.setPosition(p.x, p.y);
                // Fat ligne
                 //_target.draw(sp, _shader_rainbow);
                _target.draw(sp);
            };

            // Bounding box
            Physics::AABB bbox;

            static auto doHitbox = [&] (Physics::Hitbox hb, Physics::Vector2 const & p)
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
                Map * map = dynamic_cast<Map *>(e);
                if (map == nullptr)
                { 
                    std::cerr << "map " << e << " is null" << std::endl;
                    continue;
                }

                for (sf::Sprite & s : map->getSprites())
                {
                    s.setPosition(-500, -500);
                    _target.draw(s);
                }
            }


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
            sf::RectangleShape cameraRect(bboxSize);
            cameraRect.setOutlineColor(sf::Color::Yellow);
            cameraRect.setOutlineThickness(1.0f);
            cameraRect.setFillColor(sf::Color::Transparent);
            cameraRect.setOrigin(bboxSize.x / 2.0f, bboxSize.y / 2.0f);
            cameraRect.setPosition(sfBarycenter);
            _target.draw(cameraRect);

            // Zoom camera
            bboxSize += sf::Vector2f(50, 50);
            const sf::Vector2f & viewSize = view.getSize();
            view.zoom(std::max(bboxSize.x / viewSize.x,
                        bboxSize.y / viewSize.y));

            // HUD
            static auto draw_number = [&] (unsigned int number, sf::Vector2f const & dpos, std::array<sf::Texture, 11> const & lsChar)
            {
                constexpr float dx = -45.0f;
                //_shader_filter->setParameter("percent", (number % 1000) / 300.0);

                sf::Sprite spr(lsChar[10]);
                spr.setScale(0.5f, 0.5f);
                spr.setPosition(dpos.x + dx, dpos.y);
                // _target.draw(spr, _shader_filter);
                _target.draw(spr);
                if(number == 0)
                {
                    spr.setTexture(lsChar[0]);
                    spr.setPosition(spr.getPosition().x + dx, spr.getPosition().y);
                    // _target.draw(spr, _shader_filter);
                    _target.draw(spr);
                }
                while(number != 0)
                {
                    unsigned int n = number % 10;
                    spr.setTexture(lsChar[n]);
                    spr.setPosition(spr.getPosition().x + dx, spr.getPosition().y);
                    // _target.draw(spr, _shader_filter);
                    _target.draw(spr);
                    number /= 10;
                }
            };

            _target.setView(_target.getDefaultView());

            auto getTex = [&] (Entity * e) {
                if(e->name() == "Rick Hard")
                    return _texRickHard;
                if(e->name() == "Petit Poney")
                    return _texCharlie;
                if(e->name() == "Pedro Panda")
                    return _texPedroPanda;
                return _texRickHard;
            };

/*            std::size_t i = 0;*/
            //for(Entity * p : _playerList)
            //{
                //sf::Sprite spr(*getTex(p));
                //if(i >= 4)
                    //break;
                //if(i == 0)
                    //spr.setPosition(10.0, 10.0);
                //if(i == 1)
                    //spr.setPosition(_target.getSize().x - spr.getTexture()->getSize().x - 10.0, 10.0);
                //if(i == 2)
                    //spr.setPosition(10.0, _target.getSize().y - spr.getTexture()->getSize().y - 10.0);
                //if(i == 3)
                    //spr.setPosition(_target.getSize().x - spr.getTexture()->getSize().x - 10.0, _target.getSize().y - spr.getTexture()->getSize().y - 10.0);

                //_target.draw(spr);
                //// TODO
                //draw_number(42, spr.getPosition() + sf::Vector2f(280.0f, 25.0f), _lsChar);
                //i++;
            //}

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
