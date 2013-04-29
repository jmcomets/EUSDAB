#include <physics/controller.h>
#include <physics/hitbox.h>

namespace EUSDAB
{
    namespace Physics
    {
        Controller::Controller(Input::Controller & input_controller):
            _input(input_controller),
            _entityList()
        {
        }

        void Controller::addEntity(Entity * e)
        {
            _entityList.emplace_back(e);
        }

        void Controller::update()
        {
            for (Entity * e1 : _entityList)
            {
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

            for (Hitbox<Unit> const & h1 : a1->hitboxList())
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
                for (Hitbox<Unit> const & h2 : a2->hitboxList())
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
                        if (h1 == Hitbox<Unit>::Attack && h2 == Hitbox<Unit>::Defense)
                        {
                            // Attaque
                            _input.pushEvent(e1, Event(Event::Attack, Event::Full, Event::RisingEdge));
                            _input.pushEvent(e2, Event(Event::Damage, Event::Full, Event::RisingEdge));
                            //e1->attack(e2);
                        }
                        else if (h1 == Hitbox<Unit>::Foot && h2 == Hitbox<Unit>::Defense)
                        {
                            // Atterissage
                            _input.pushEvent(e1, Event(Event::Ground, Event::Full, Event::RisingEdge));
                            //e1->physics(e2);
                        }
                        else if (h1 == Hitbox<Unit>::Defense && h2 == Hitbox<Unit>::Defense)
                        {
                            // Collision
                            //_input.pushEvent(e1, Event(Event::Collision, Event::Full, Event::RisingEdge));
                            //e1->physics(e2);
                        }
                        else if (h1 == Hitbox<Unit>::Grab && h2 == Hitbox<Unit>::Grabable)
                        {
                            // Grab
                            _input.pushEvent(e1, Event(Event::Grab, Event::Full, Event::RisingEdge));
                            //e1->grab(e2);
                        }
                    }
                }
            }
        }
    }
}
