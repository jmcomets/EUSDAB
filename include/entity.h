#ifndef ENTITY_H_
#define ENTITY_H_

#include <unordered_map>

#include <movement.h>

namespace EUSDAB
{
    namespace Input
    {
        class State;
    }

    class Entity
    {
        public:
            Entity();
            Entity(Entity &&) = default;
            Entity(const Entity &) = delete;
            virtual ~Entity();
            Entity & operator=(const Entity &) = delete;

            void state(Input::State *);
            Input::State * state() const;

            void state(Movement, Input::State *);
            Input::State * state(Movement) const;

        protected:
            Input::State * _current;
            std::unordered_map<Movement, Input::State *, std::hash<int>> _states;
    };
}

#endif
