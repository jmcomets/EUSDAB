#include <physics/controller.h>
#include <physics/hitbox.h>
#include <algorithm>
#include <sstream>
#include <cassert>
#include <iostream>

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
            using Input::Event;

            for (Entity * e1 : _entityList)
            {
                // handleEntityTransform(e1);
                handleWorldEntity(e1);

                // Handle speed / acceleration

                // TODO faire un transformation de test.
                // Si il n'y a pas de collision, on garde cette transformation
                // Si il y a une collision, on revient à la précédente
                // et on divise la vitesse par 2 selon la direction
                // A faire pour l'axe X et l'axe Y
                // Créer une méthode applyX/applyY pour entity ?

                // TODO récupérer la sémantique de la collision
                // depuis la méthode handleEntityCollision.
                // Gérer la réponse dans cette méthode.

                Transform oldTrans;
                State * s = e1->state();

                bool canMoveY = true;
                oldTrans = e1->physics();

                if (s != nullptr)
                {
                    e1->physics().applyY(s->transformation());
                    if(e1->gravitable())
                        e1->physics().velocity().y += _world->gravity().y;
                }

                e1->physics().updateY();
                for (Entity * e2 : _entityList)
                {
                    if (e1 == e2) { continue; }

                    Hitbox::Semantic_type s = handleEntityCollision(e1, e2);

                    if(s & Hitbox::Collision)
                    {
                        _input.pushEvent(e1, Event(Event::Collide));
                        canMoveY = false;
                    }
                    if(s & Hitbox::Attack)
                    {
                        _input.pushEvent(e1, Event(Event::Attack));
                        _input.pushEvent(e2, Event(Event::Damage));
                    }
                    if(s & Hitbox::Grab)
                    {
                        _input.pushEvent(e1, Event(Event::Grab));
                    }
                }
                if(canMoveY == false)
                {
                    e1->physics() = oldTrans;
                    e1->physics().velocity().y = 0;
                    e1->physics().acceleration().y = 0;
                }
                if(std::abs(e1->physics().velocity().y) < std::numeric_limits<float>::epsilon()
                        || (e1->physics().velocity().y > 0 && canMoveY == false))
                {
                    //std::cout << "Physics controller : " << e1->physics() << std::endl;

                    _input.pushEvent(e1, Input::Event(Input::Event::Ground));
                }

                bool canMoveX = true;
                oldTrans = e1->physics();
                if (s != nullptr)
                {
                    // s->transformation().update();
                    e1->physics().applyX(s->transformation());
                    if(e1->gravitable())
                        e1->physics().velocity().x += _world->gravity().x;
                }

                e1->physics().updateX();
                for (Entity * e2 : _entityList)
                {
                    if (e1 == e2) { continue; }

                    Hitbox::Semantic_type s = handleEntityCollision(e1, e2);

                    if(s & Hitbox::Collision)
                    {
                        _input.pushEvent(e1, Event(Event::Collide));
                        canMoveX = false;
                    }
                    if(s & Hitbox::Attack)
                    {
                        _input.pushEvent(e1, Event(Event::Attack));
                        _input.pushEvent(e2, Event(Event::Damage));
                    }
                    if(s & Hitbox::Grab)
                    {
                        _input.pushEvent(e1, Event(Event::Grab));
                    }
                }


                if(canMoveX == false)
                {
                    e1->physics() = oldTrans;
                    e1->physics().velocity().x = 0;
                    e1->physics().acceleration().x = 0;
                }


                //handleEntityMovement(e1);

                //e1->hitbox().set(e1->position());
            }
        }

        Hitbox::Semantic_type Controller::handleEntityCollision(Entity * e1, Entity * e2)
        {
            // Shorten code a little
            Hitbox::Semantic_type flag = Hitbox::Nothing;

            Hitbox h1 = e1->hitbox();
            Hitbox h2 = e2->hitbox();
            h1.translate(e1->position());
            h2.translate(e2->position());
            if(h1.collides(h2))
            {
                if(h1 == Hitbox::Collision && h2 == Hitbox::Collision)
                {
                    flag |= Hitbox::Collision;
                }
            }

            State * s1 = e1->state();
            if (s1 == nullptr)
            {
                return flag;
            }

            Animation * a1 = s1->animation();
            if (a1 == nullptr)
            {
                return flag;
            }

            if(a1 != nullptr)
            {
                h2 = e2->hitbox();
                h2.translate(e2->position());
                for(Hitbox h1 : a1->hitboxList())
                {
                    h1.translate(e1->position());
                    if(h1.collides(h2))
                    {
                        if(h1 == Hitbox::Collision && h2 == Hitbox::Collision)
                        {
                            flag |= Hitbox::Collision;
                        }
                    }
                }
            }

            State * s2 = e2->state();
            if(s2 != nullptr)
            {
                Animation * a2 = s2->animation();
                if(a2 != nullptr)
                {
                    h1 = e1->hitbox();
                    h1.translate(e1->position());
                    for(Hitbox h2 : a2->hitboxList())
                    {
                        h2.translate(e2->position());
                        if(h1.collides(h2))
                        {
                            if(h1 == Hitbox::Collision && h2 == Hitbox::Collision)
                            {
                                flag |= Hitbox::Collision;
                            }
                        }
                    }
                }
            }

            for (Hitbox h1 : a1->hitboxList())
            {
                // Do not collide if entity state is not defined
                State * s2 = e2->state();
                if (s2 == nullptr) { continue; }

                // Do not collide if state animation is not defined
                Animation * a2 = s2->animation();
                if (a2 == nullptr) { continue; }

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
                        // Collision treatment
                        if (h1 == Hitbox::Attack && h2 == Hitbox::Defense)
                        {
                            if(_playerList.find(e2) != _playerList.end())
                            {
                                // Attaque
                                e1->attack(e2);
                            }

                            flag |= Hitbox::Attack;
                        }
                        else if (h1 == Hitbox::Foot && h2 == Hitbox::Defense)
                        {
                            // Atterissage
                            // _input.pushEvent(e1, Event(Event::Ground));
                            flag |= Hitbox::Foot;
                        }
                        else if (h1 == Hitbox::Defense && h2 == Hitbox::Defense)
                        {
                            // OSEF
                            // _input.pushEvent(e1, Event(Event::Collide));
                            flag |= Hitbox::Defense;
                        }
                        else if (h1 == Hitbox::Grab && h2 == Hitbox::Grabable)
                        {
                            // Grab
                            //e1->grab(e2);

                            flag |= Hitbox::Grab;
                        }
                        else if (h1 == Hitbox::Collision && h2 == Hitbox::Collision)
                        {
                            // Collision

                            flag |= Hitbox::Collision;
                        }
                    }
                }
            }

            return flag;
        }

        void Controller::handleEntityTransform(Entity * e)
        {
            State * s = e->state();
            if (s != nullptr)
            {
                // s->transformation().update();
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
                e->physics().update();
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
                    // Dirty hack
                    if(e->position().y > _world->aabb().max().y + 150 ||
                        e->position().x < _world->aabb().min().x - 50 ||
                        e->position().x > _world->aabb().max().x + 50)
                    {
                        std::cout << "DEAAAAAAATTTTHHHH" << std::endl;
                        s->onExitWorld();
                        return;
                    }

                    /*// Instanciation of lambda for containment-check*/
                    ////  for all physical entities
                    //auto notContainedInWorld = [&](const Hitbox & hb)
                    //{
                        //return _world->contains(hb) == false;
                    //};

                    //// If the entity isn't contained in the world,
                    ////  ie : all of its hitboxes aren't in the world
                    ////  fire a onExitWorld call on its State
                    //const Animation::HitboxList & hitboxList = a->hitboxList();
                    //if (std::all_of(hitboxList.begin(), hitboxList.end(),
                                //notContainedInWorld))
                    //{
                        //// TODO does not work !
                        //s->onExitWorld();
                    /*}*/
                }
            }
        }
    }
}
