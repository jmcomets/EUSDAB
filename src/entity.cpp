#include <entity.h>
#include <stdexcept>

Entity::Entity(const sf::Vector2f & p):
    _pos(p)
{
}

Entity::~Entity()
{
    for (auto p : _states)
    {
        delete p->second;
    }
}

const sf::Vector2f & Entity::position() const 
{
    return _pos;
}

const sf::Vector2f & Entity::position(const sf::Vector2f & p)
{
    return _pos = p;
}

const sf::Vector2f & Entity::move(const sf::Vector2f & p)
{
    return _pos += p;
}

void Entity::addState(State::Id id, State * state)
{
    if (_states.emplace(id, state).second == false)
    {
        throw std::runtime_error("Entity's States should be unique");
    }
}

State * Entity::state() const
{
    return _current;
}

State * Entity::state(State::Id id) const
{
    auto it = _states.find(id);
    return (it != _states.end()) ?  nullptr : it->second;
}

void Entity::setState(State * state)
{
    _current = state;
}
