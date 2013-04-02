#include <physics/controller.h>

#include <input/controller.h>

namespace EUSDAB
{
    Controller::Controller(Input::Controller & __input_controller):
        _input_controller(__input_controller),
        _entity_list()
    {
    }

    Controller::~Controller()
    {
    }

    void Controller::addEntity(Entity * __e)
    {
        _entity_list.emplace_back(__e);
    }

    void Controller::update()
    {
        for(Entity * e : _entity_list)
            for(Entity * other : _entity_list)
                if(e != other && e->hitbox().collide(other->hitbox()))
                {
                    Hitbox & h1 = e->hitbox();
                    Hitbox & h2 = other->hitbox();
                    // Traitement de la collision
                    if(h1 == Hitbox::Attack && h2 == Hitbox::Defense)
                    {
                        // Attaque
                        _input_controller.sendEvent(e, Input::Event::Attack(e, other));
                        _input_controller.sendEvent(other, Input::Event::Damage(e, other));
                        e->attack(other);
                    }
                    else if(h1 == Hitbox::Foot && h2 == Hitbox::Defense)
                    {
                        // Atterissage
                        _input_controller.sendEvent(e, GroundEvent(other));
                        e->physics(other);
                    }
                    else if(h1 == Hitbox::Defense && h2 == Hitbox::Defense)
                    {
                        // Collision
                        _input_controller.sendEvent(e, CollisionEvent(other));
                        e->physics(other);
                    }
                    else if(h1 == Hitbox::Grab && h2 == Hitbox::Grabable)
                    {
                        // Grab
                        _input_controller.sendEvent(e, GrabEvent(other));
                        e->grab(other);
                    }
                }
    }
}
