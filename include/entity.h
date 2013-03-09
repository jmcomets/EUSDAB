#ifndef ENTITY_H_
#define ENTITY_H_

#include <SFML/System/Vector2.hpp>
#include <graphics.h>
#include <joystickState.h>

class Entity
{
    public:
        // Default constructor
        Entity();

        // Value constructor
        Entity(const sf::Vector2f &);

        // Move constructor
        Entity(Entity &&);

        // Copy constructor
        Entity(const Entity &);

        // Destructor
        virtual ~Entity();

        // Assignment operator
        Entity & operator=(const Entity &);

        // Get position
        sf::Vector2f position() const;

        // Set position
        void position(const sf::Vector2f &);

        // Move Entity
        void move(const sf::Vector2f &);

        // Update method
        virtual void update(JoystickState const &) = 0;

        // Render method
        virtual void render(Graphics::Target &, Graphics::RenderStates) = 0;

    private:
        // Absolute position
        sf::Vector2f _pos;
};

#endif // ENTITY_H_
