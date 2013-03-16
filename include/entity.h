#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>

// #include <input/state.h>

namespace EUSDAB
{
    namespace Input
    {
        class State
        {
            public:
                typedef int Id;
        };
    }

    class Entity
    {
        public:
            Entity() = default;
            Entity(Entity &&) = default;
            Entity(Entity const &) = delete;
            Entity & operator=(Entity const &) = delete;

            virtual ~Entity();

            void state(Input::State *);
            Input::State * state() const;

            void state(Input::State::Id, Input::State *);
            Input::State * state(Input::State::Id) const;

        protected:
            Input::State * _current;
            std::unordered_map<Input::State::Id, Input::State *, std::hash<int>> _states;
    };
}

#endif
