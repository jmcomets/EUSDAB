#include <physics/controller.h>
#include <physics/hitbox.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cassert>

namespace EUSDAB
{
    namespace Physics
    {
        Controller::Controller(Input::Controller & input_controller,
                World * world):
            _input(input_controller),
            _world(world),
            _entityList()
        {
            assert(_world != nullptr);
        }

        Controller::~Controller()
        {
            delete _world;
        }

        void Controller::addEntity(Entity * e)
        {
            assert(e != nullptr);
            _entityList.push_back(e);
        }

        void Controller::update()
        {
            for (Entity * e1 : _entityList)
            {
                handleEntityTransform(e1);
                handleWorldEntity(e1);
                for (Entity * e2 : _entityList)
                {
                    if (e1 != e2)
                    {
                        handleEntityCollision(e1, e2);
                    }
                }
                handleEntityMovement(e1);
            }
        }

        void Controller::handleEntityCollision(Entity * e1, Entity * e2)
        {
            State * s1 = e1->state();
            if (s1 == nullptr)
            {
                return;
            }

            Animation * a1 = s1->animation();
            if (a1 == nullptr)
            {
                return;
            }

            for (Hitbox h1 : a1->hitboxList())
            {
                // Do not collide if entity state is not defined
                State * s2 = e2->state();
                if (s2 == nullptr)
                {
                    continue;
                }

                // Do not collide if state animation is not defined
                Animation * a2 = s2->animation();
                if (a2 == nullptr)
                {
                    continue;
                }

                h1.translate(e1->position());
                // All is good, handle collision
                for (Hitbox h2 : a2->hitboxList())
                {
                    // TODO: Gestion de la sémentique dans les collision
                    // Exemple de regle de sémentique :
                    // Attack & Defense
                    // Grab & Grabable
                    // Foot & Defense
                    h2.translate(e2->position());
                    if (h1.collides(h2))
                    {
                        // Shorten code a little
                        using Input::Event;

                        static auto hbStr = [] (const Hitbox & hb)
                        {
                            std::ostringstream oss;
                            oss << "Hitbox[ ";
                            for (const Hitbox::AABB & aabb : hb.aabbList())
                            {
                                oss << "AABB(x = " << aabb.x() << ", y = "
                                    << aabb.y() << ", width = "
                                    << aabb.width() << ", height = "
                                    << aabb.height() << ") ";
                            }
                            oss << "]";
                            return oss.str();
                        };

                        // Collision treatment
                        if (h1 == Hitbox::Attack && h2 == Hitbox::Defense)
                        {
                            // Attaque
                            _input.pushEvent(e1, Event(Event::Attack));
                            _input.pushEvent(e2, Event(Event::Damage));
                            //e1->attack(e2);
                        }
                        else if (h1 == Hitbox::Foot && h2 == Hitbox::Defense)
                        {
                            // Atterissage
                            std::cout << "collision between " << hbStr(h1)
                                << " and " << hbStr(h2) << std::endl;
                            e1->physics().velocity().setY(0);

                            _input.pushEvent(e1, Event(Event::Ground));
                        }
                        else if (h1 == Hitbox::Defense && h2 == Hitbox::Defense)
                        {
                            // Collision
                            _input.pushEvent(e1, Event(Event::Collide));
                        }
                        else if (h1 == Hitbox::Grab && h2 == Hitbox::Grabable)
                        {
                            // Grab
                            _input.pushEvent(e1, Event(Event::Grab));
                            //e1->grab(e2);
                        }
                    }
                }
            }
        }

        void Controller::handleEntityTransform(Entity * e)
        {
            State * s = e->state();
            if (s != nullptr)
            {
                s->transformation().update();
                e->physics().apply(s->transformation());
                if(e->gravitable())
                    e->physics().velocity() += _world->gravity();
            }
        }

        void Controller::handleEntityMovement(Entity * e)
        {
            State * s = e->state();
            if (s != nullptr)
            {
                Physics::Vector2 p = e->position();
                std::cout << p.y() << std::endl;
                e->physics().update();

                Animation * a = s->animation();
                if (a != nullptr)
                {
                    Physics::Vector2 v = e->position() - p;
                    if (v.norm())
                    {
                        for (Hitbox & hb : a->hitboxList())
                        {
                            hb.translate(v);
                        }
                    }
                }
            }
        }

        void Controller::handleWorldEntity(Entity * e)
        {
            State * s = e->state();
            if (s != nullptr)
            {
                Animation * a = s->animation();
                if (a != nullptr)
                {
                    // Instanciation of lambda for containment-check
                    //  for all physical entities
                    auto notContainedInWorld = [&](const Hitbox & hb)
                    {
                        return _world->contains(hb) == false;
                    };

                    // If the entity isn't contained in the world,
                    //  ie : all of its hitboxes aren't in the world
                    //  fire a onExitWorld call on its State
                    const Animation::HitboxList & hitboxList = a->hitboxList();
                    if (std::all_of(hitboxList.begin(), hitboxList.end(),
                                notContainedInWorld))
                    {
                        // TODO does not work !
                        s->onExitWorld();
                    }
                }
            }
        }
    }
}
