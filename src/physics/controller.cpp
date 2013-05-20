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
            _entityList(),
            _playerList()
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
                std::cout << e1->name() << " : " << e1->physics() << std::endl;
                handleEntityTransform(e1);
                handleWorldEntity(e1);

                // Handle speed / acceleration 
                bool canMoveX = true;
                bool canMoveY = true;

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

                oldTrans = e1->physics();

                if (s != nullptr)
                {
                    // s->transformation().update();
                    e1->physics().applyY(s->transformation());
                    if(e1->gravitable())
                        e1->physics().velocity().y += _world->gravity().y;
                }

                e1->physics().updateY();
                for (Entity * e2 : _entityList)
                {
                    if (e1 == e2) { continue; }

                    Hitbox::Semantic_type s = handleEntityCollision(e1, e2);
                    if (s & Hitbox::Defense || s & Hitbox::Grab)
                    {
                        Hitbox::Semantic_type s = handleEntityCollision(e1, e2);
                        if(s & Hitbox::Grab
                                || s & Hitbox::Foot)
                        {
                            canMoveY = false;
                        }
                    }
                }
                if(canMoveY == false)
                {
                    e1->physics() = oldTrans;
                    e1->physics().velocity().y /= 2;
                    e1->physics().acceleration().y /= 2;

                    if(e1->physics().velocity().y < 0.5 &&
                            e1->physics().velocity().y > -0.5)
                        e1->physics().velocity().y = 0;
                    if(e1->physics().acceleration().y < 0.5 &&
                            e1->physics().acceleration().y > -0.5)
                        e1->physics().acceleration().y = 0;
                }

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
                    if (s & Hitbox::Grab || s & Hitbox::Foot)
                    {
                        Hitbox::Semantic_type s = handleEntityCollision(e1, e2);
                        if(s & Hitbox::Defense
                                || s & Hitbox::Grab)
                        {
                            canMoveX = false;
                        }
                    }
                }
                if(canMoveX == false)
                {
                    e1->physics() = oldTrans;
                    e1->physics().velocity().x /= 2;
                    e1->physics().acceleration().x /= 2;
                    //std::cout << e1 << " " << e1->position().x << " " << e1->position().y << " " << oldTrans.position().x << " " << oldTrans.position().y << std::endl;

                    if(e1->physics().velocity().x < 0.5 &&
                            e1->physics().velocity().x > -0.5)
                        e1->physics().velocity().x = 0;
                    if(e1->physics().acceleration().x < 0.5 &&
                            e1->physics().acceleration().x > -0.5)
                        e1->physics().acceleration().x = 0;
                }

                //handleEntityMovement(e1);
            }
        }

        Hitbox::Semantic_type Controller::handleEntityCollision(Entity * e1, Entity * e2)
        {
            State * s1 = e1->state();
            if (s1 == nullptr)
            {
                return Hitbox::Nothing;
            }

            Animation * a1 = s1->animation();
            if (a1 == nullptr)
            {
                return Hitbox::Nothing;
            }

            Hitbox::Semantic_type flag = Hitbox::Nothing;

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
                        // Shorten code a little
                        using Input::Event;

                        // Collision treatment
                        if (h1 == Hitbox::Attack && h2 == Hitbox::Defense)
                        {
                            if(_playerList.find(e2) != _playerList.end())
                            {
                                // Attaque
                                _input.pushEvent(e1, Event(Event::Attack));
                                _input.pushEvent(e2, Event(Event::Damage));
                                e1->attack(e2);

                                flag |= Hitbox::Attack;
                            }
                        }
                        else if (h1 == Hitbox::Foot && h2 == Hitbox::Defense)
                        {
                            // Atterissage
                            _input.pushEvent(e1, Event(Event::Ground));
                            flag |= Hitbox::Foot;
                        }
                        else if (h1 == Hitbox::Defense && h2 == Hitbox::Defense)
                        {
                            // Collision
                            _input.pushEvent(e1, Event(Event::Collide));
                            flag |= Hitbox::Defense;
                        }
                        else if (h1 == Hitbox::Grab && h2 == Hitbox::Grabable)
                        {
                            // Grab
                            _input.pushEvent(e1, Event(Event::Grab));
                            //e1->grab(e2);

                            flag |= Hitbox::Grab;
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
