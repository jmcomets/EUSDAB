#include <entity.h>

#include <stdexcept>

#include <input/state.h>

namespace EUSDAB
{
    Entity::Entity(Input::State * current):
        _current(current),
        _states()
    {
    }

    Entity::~Entity()
    {
        for (auto p : _states)
        {
            delete p.second;
        }
    }

    void Entity::state(Input::State * state)
    {
        _current = state;
    }

    Input::State * Entity::state() const
    {
        return _current;
    }

    void Entity::state(Movement id, Input::State * state)
    {
        if (_states.emplace(id, state).second == false)
        {
            throw std::runtime_error("Entity's States should be unique");
        }
        state->entity(this);
    }

    Input::State * Entity::state(Movement id) const
    {
        auto it = _states.find(id);
        return (it != _states.end()) ?  nullptr : it->second;
    }
}

