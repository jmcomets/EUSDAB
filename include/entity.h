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
    class Attack;

    // Forward declarations
    namespace Input
    {
        class State;
    }

    class Entity
    {
        public:
            Entity(Entity &&) = default;
            Entity(Entity const &) = delete;
            Entity & operator=(Entity const &) = delete;

            Entity();
            virtual ~Entity();

            // General

            // Add a new State to the Entity
            void addState(const Movement &, Input::State *);

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
            //HitboxList & hitboxList();

            // Add another hitbox
            void addHitbox(const Hitbox &);

            // Input module

            // Get/Set the Entity's state, either directly
            //   or by lookup by Movement (ID).
            void setState(const Movement &);
            void setState(Input::State *);
            Input::State * state() const;
            Input::State * state(const Movement &) const;

        protected:
            // General
            std::string _name;

            // Attack
            Attack * _attack;

            // Physics
            HitboxList _hitboxList;

            // Input
            Input::State * _current;
            std::unordered_map<Movement, Input::State *> _states;
    };
}

#endif
