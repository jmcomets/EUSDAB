#include <entity.h>
#include <stdexcept>
#include <state.h>

namespace EUSDAB
{
    Entity::Entity():
        _name(),
        _attack(nullptr),
        _hitboxList(),
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
        State * st = state(id);
        if (st == nullptr)
        {
            throw std::runtime_error("Unknown Entity's state id");
        }
        else
        {
            _current = st;
        }
    }

    void Entity::setState(State * state)
    {
        _current = state;
    }

    void Entity::setName(const std::string & name)
    {
        _name = name;
    }

    State * Entity::state() const
    {
        return _current;
    }

    State * Entity::state(const Movement & id) const
    {
        auto it = _states.find(id);
        return (it != _states.end()) ? it->second : nullptr;
    }

    std::string Entity::name() const
    {
        return _name;
    }

    void Entity::addState(const Movement & id, State * state)
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
