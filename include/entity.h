#ifndef ENTITY_H_
#define ENTITY_H_

#include <SFML/System/Vector2.hpp>
#include <graphics.h>
#include <view.h>

class Entity
{
    public:
        Entity() = default;
        Entity(const sf::Vector2f &);
        Entity(Entity &&) = default;
        Entity(const Entity &) = default;
        virtual ~Entity();
        Entity & operator=(const Entity &) = default;
        const sf::Vector2f & position() const;
        const sf::Vector2f & position(const sf::Vector2f &);
        const sf::Vector2f & move(const sf::Vector2f &);
        virtual void update() = 0;
        virtual void render(Graphics::Target &, Graphics::RenderStates) = 0;

    protected:
        sf::Vector2f _pos;
};

#endif
