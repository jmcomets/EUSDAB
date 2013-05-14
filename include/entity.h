#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>
#include <set>
#include <stdextension.h>
#include <input/speaker.h>
#include <physics/config.h>
#include <physics/component.h>
#include <movement.h>
//#include <attack.h>

namespace EUSDAB
{
    // Forward declarations
    class State;
    class Attack;

    class Entity: public Input::Speaker
    {
        public:
            Entity(Entity &&) = default;
            Entity(Entity const &) = delete;
            Entity & operator=(Entity const &) = delete;

            Entity();
            virtual ~Entity();

            // General

            // Get/Set the Entity's name
            std::string name() const;
            void setName(const std::string &);

            // Get the Entity's position
            const Physics::Vector2 & position() const;
            // ...non-const version
            Physics::Vector2 & position();

            // Attack module

            // Get/Set the attack
            Attack * attack() const;
            void setAttack(Attack *);

            // Actually attack another entity
            void attack(Entity *); // FIXME const ? 

            // State module

            // Get the Entity's state directly
            State * state() const;
            // ...or by lookup by movement
            State * state(const Movement &) const;

            // Set the Entity's state directly
            void setState(State *);
            // ...or by lookup by movement (throws an 
            //   std::runtime_error if the given ID 
            //   isn't defined by an associated state). 
            void setState(const Movement &);

            // Add a new state to the Entity, identified
            //   by its movement (throws an std::runtime_error
            //   if the state's ID is already associated to another
            //   state).
            void addState(State *);

        private:
            // General
            std::string _name;

            // Attack
            Attack * _attack;

            // Positioning
            Physics::Component _physics;

            // State
            State * _current;
            std::set<State *, std::less_ptr<State>> _states;
    };
}

#endif
