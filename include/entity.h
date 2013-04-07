#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>
#include <unordered_map>
#include <movement.h>
#include <physics/config.h>
#include <physics/hitbox.h>
//#include <attack.h>

namespace EUSDAB
{
    // TODO design and write this module
    class Attack;

    // Forward declarations
    namespace Input
    {
        class State;
    }

    // TODO physics module should be moved either in a 
    //   component or in state, using delegation afterwards.
    class Entity
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

            // Attack module

            // Get/Set the attack
            const Attack & attack() const;
            void setAttack(Attack *);

            // Actually attack another entity
            void attack(Entity *); // FIXME const ? 

            // Physics module

            // Exposed types
            typedef Physics::Hitbox<Physics::Unit> Hitbox;
            typedef std::vector<Hitbox> HitboxList;

            // Get the hitbox list
            const HitboxList & hitboxList() const;
            // ...non const version
            //HitboxList & hitboxList();

            // Add a new hitbox to the Entity
            void addHitbox(const Hitbox &);

            // Input module

            // Get the Entity's state directly
            Input::State * state() const;
            // ...or by lookup by movement
            Input::State * state(const Movement &) const;

            // Set the Entity's state directly
            void setState(Input::State *);
            // ...or by lookup by movement (throws an 
            //   std::runtime_error if the given ID 
            //   isn't defined by an associated state). 
            void setState(const Movement &);

            // Add a new state to the Entity, identified
            //   by its movement (throws an std::runtime_error
            //   if the state's ID is already associated to another
            //   state).
            void addState(const Movement &, Input::State *);

        protected:
            // General
            std::string _name;

            // Attack
            Attack * _attack;

            // Physics
            HitboxList _hitboxList;

            // View TODO
            //View _view;

            // Input
            Input::State * _current;
            std::unordered_map<Movement, Input::State *> _states;
    };
}

#endif
