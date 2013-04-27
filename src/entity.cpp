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
        for (auto s : _states)
        {
            delete s;
        }
    }

    void Entity::setState(State * state)
    {
        _current = state;
    }

    void Entity::setState(const Movement & mvt)
    {
        State * s = state(mvt);
        if (s == nullptr)
        {
            throw std::runtime_error("No state defined for given movement");
        }
        _current = s;
    }

    void Entity::setName(const std::string & name)
    {
        _name = name;
    }

    State * Entity::state() const
    {
        return _current;
    }

    State * Entity::state(const Movement & mvt) const
    {
        State s;
        s.setMovement(mvt);
        auto it = _states.find(&s);
        return it != _states.end() ? *it : nullptr;
    }

    std::string Entity::name() const
    {
        return _name;
    }

    void Entity::addState(State * state)
    {
        if (_states.insert(state).second == false)
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
