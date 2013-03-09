#include <entity.h>

Entity::Entity(const sf::Vector2f & p):
    _pos(p)
{
}

Entity::~Entity()
{
}

sf::Vector2f Entity::position() const 
{
    return _pos;
}

void Entity::position(const sf::Vector2f & p)
{
}

void Entity::move(const sf::Vector2f & p)
{
    _pos += p;
}
