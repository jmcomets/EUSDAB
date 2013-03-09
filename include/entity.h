#ifndef ENTITY_H_
#define ENTITY_H_

#include <vector.h>

class Entity
{
    public:
        // Default constructor
        Entity();

        // Value constructor
        Entity(const Vector &);

        // Move constructor
        Entity(Entity &&);

        // Copy constructor
        Entity(const Entity &);

        // Destructor
        virtual ~Entity();

        // Assignment operator
        Entity & operator=(const Entity &);

        // Get position
        Vector position() const;

        // Set position
        void position(const Vector &);

        // Move Entity
        void move(const Vector &);

        // Update method
        virtual void update() = 0;

        // Render method
        virtual void render(Graphics::Target &, Graphics::Transformation) = 0;

    private:
        // Absolute position
        Vector _pos;
};

#endif // ENTITY_H_
