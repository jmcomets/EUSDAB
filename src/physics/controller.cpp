#include <physics/controller.h>
#include <physics/hitbox.h>
#include <algorithm>
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

        void Controller::addEntity(Entity * e)
        {
            assert(e != nullptr);
            _entityList.push_back(e);
        }

        void Controller::update()
        {
            for (Entity * e1 : _entityList)
            {
                handleWorldEntity(e1);
                for (Entity * e2 : _entityList)
                {
                    if (e1 != e2)
                    {
                        handleEntityCollision(e1, e2);
                    }
                }
            }
        }

        void Controller::handleEntityCollision(Entity * e1, Entity * e2)
        {
            // Concept check
            assert(e1 != nullptr);
            assert(e2 != nullptr);

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

            for (Hitbox const & h1 : a1->hitboxList())
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

                // All is good, handle collision
                for (Hitbox const & h2 : a2->hitboxList())
                {
                    // TODO: Gestion de la sémentique dans les collision
                    // Exemple de regle de sémentique :
                    // Attack & Defense
                    // Grab & Grabable
                    // Foot & Defense
                    if (h1.collides(h2))
                    {
                        // Shorten code a little
                        using Input::Event;

                        // Collision treatment
                        if (h1 == Hitbox::Attack && h2 == Hitbox::Defense)
                        {
                            // Attaque
                            _input.pushEvent(e1, Event(Event::Attack));
                            _input.pushEvent(e2, Event(Event::Damage));
                            e1->attack(e2);
                        }
                        else if (h1 == Hitbox::Foot && h2 == Hitbox::Defense)
                        {
                            // Atterissage
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

        void Controller::handleWorldEntity(Entity * e)
        {
            // Concept check
            assert(e != nullptr);

            State * s = e->state();
            if (s != nullptr)
            {
                Animation * a = s->animation();
                if (a != nullptr)
                {
                    // Instanciation of lambda for containment-check
                    //  for all physical entities
                    auto containedInWorld = [&](const Hitbox & hb)
                    {
                        return _world->contains(hb);
                    };

                    // If the entity isn't contained in the world,
                    //  fire a onExitWorld call on its State
                    const Animation::HitboxList & hitboxList = a->hitboxList();
                    if (std::all_of(hitboxList.begin(), hitboxList.end(),
                            containedInWorld) == false)
                    {
                        s->onExitWorld();
                    }
                }
            }
        }
    }
}
