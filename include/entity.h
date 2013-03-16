#ifndef ENTITY_H_
#define ENTITY_H_

#include <unordered_map>
#include <input/state.h>

namespace EUSDAB
{
    class Entity
    {
        public:
            Entity() = default;
            Entity(Entity &&) = default;
            Entity(const Entity &) = delete;
            virtual ~Entity();
            Entity & operator=(const Entity &) = delete;

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
