#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>
#include <unordered_map>

#include <movement.h>

#include <physics/hitbox.h>

namespace EUSDAB
{
    class Attack;

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

            void setState(const Movement &);
            void setState(Input::State *);

            void setName(const std::string &);

            Input::State * state() const;
            Input::State * state(const Movement &) const;

            std::string name() const;

            std::vector<Physics::Hitbox_t> const & hitboxList() const;
            Attack const & attack() const;

    void addState(const Movement &, Input::State *);

        protected:
            std::string _name;

            // Module Input
            Input::State * _current;
            std::unordered_map<Movement, Input::State *> _states;
    };
}

#endif
