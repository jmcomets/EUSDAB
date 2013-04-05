#include <physics/controller.h>

#include <entity.h>
#include <input/controller.h>

namespace EUSDAB
{
    namespace Physics
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
                    for(Physics::Hitbox_t const & h1 : e->hitboxList())
                        for(Physics::Hitbox_t const & h2 : other->hitboxList())
                            if(e != other && h1.collide(h2))
                            {
                                // Traitement de la collision
                                if(h1 == Hitbox_t::Attack && h2 == Hitbox_t::Defense)
                                {
                                    // Attaque
                                    _input_controller.pushEvent(e, Input::Event::Attack(e, other));
                                    _input_controller.pushEvent(other, Input::Event::Damage(e, other));
                                    e->attack(other);
                                }
                                else if(h1 == Hitbox_t::Foot && h2 == Hitbox_t::Defense)
                                {
                                    // Atterissage
                                    _input_controller.pushEvent(e, GroundEvent(other));
                                    e->physics(other);
                                }
                                else if(h1 == Hitbox_t::Defense && h2 == Hitbox_t::Defense)
                                {
                                    // Collision
                                    _input_controller.pushEvent(e, CollisionEvent(other));
                                    e->physics(other);
                                }
                                else if(h1 == Hitbox_t::Grab && h2 == Hitbox_t::Grabable)
                                {
                                    // Grab
                                    _input_controller.pushEvent(e, GrabEvent(other));
                                    e->grab(other);
                                }
                            }
        }
    }
}
