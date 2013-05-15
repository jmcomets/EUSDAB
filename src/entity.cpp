#include <entity.h>
#include <stdexcept>
#include <state.h>
#include <iostream>

namespace EUSDAB
{
    Entity::Entity():
        Input::Speaker(),
        _name(),
        _attack(nullptr),
        _physics(),
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
        setListener(state);
    }

    void Entity::setState(const Movement & mvt)
    {
        State * s = state(mvt);
        if (s == nullptr)
        {
            throw std::runtime_error("No state defined for given movement");
        }
        setState(s);
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
        State s(mvt);
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
        state->setEntity(this);
    }

    const Physics::Vector2 & Entity::position() const
    {
        return _physics.position();
    }

    Physics::Vector2 & Entity::position()
    {
        return _physics.position();
    }

    const Physics::Transform & Entity::physics() const
    {
        return _physics;
    }

    Physics::Transform & Entity::physics()
    {
        return _physics;
    }
}
