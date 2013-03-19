#ifndef ENTITY_H
#define ENTITY_H

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
            Entity(Entity &&) = default;
            Entity(Entity const &) = delete;
            Entity & operator=(Entity const &) = delete;

            Entity(Input::State * current = nullptr);
            virtual ~Entity();

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
