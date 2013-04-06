#include <entity.h>
#include <stdexcept>
#include <input/state.h>

namespace EUSDAB
{
    Entity::Entity():
        _name(),
        _attack(nullptr),
        _current(nullptr),
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

    void Entity::setState(const Movement & id)
    {
        Input::State * st = state(id);
        if (st == nullptr)
        {
            throw std::runtime_error("Unknown state id");
        }
        else
        {
            _current = st;
        }
    }

    void Entity::setState(Input::State * state)
    {
        _current = state;
    }

    void Entity::setName(const std::string & name)
    {
        _name = name;
    }

    Input::State * Entity::state() const
    {
        return _current;
    }

    Input::State * Entity::state(const Movement & id) const
    {
        auto it = _states.find(id);
        return (it != _states.end()) ? it->second : nullptr;
    }

    std::string Entity::name() const
    {
        return _name;
    }

    void Entity::addState(const Movement & id, Input::State * state)
    {
        if (_states.insert(std::make_pair(id, state)).second == false)
        {
            throw std::runtime_error("Entity's states should be unique");
        }
        state->entity(this);
    }

    const Entity::HitboxList & Entity::hitboxList() const
    {
        return _hitboxList;
    }
}
