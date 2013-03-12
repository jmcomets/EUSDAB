#include <entity.h>

Entity::Entity(const sf::Vector2f & p):
    _pos(p)
{
}

Entity::~Entity()
{
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
