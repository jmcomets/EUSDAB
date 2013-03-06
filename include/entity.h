#ifndef ENTITY_H_
#define ENTITY_H_

#include <vector.h>
#include <action.h>

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

        // Get/Set the action
        Action * action() const;
        Action * action(Action *);

    private:
        // Absolute position
        Vector _pos;
        
        // Entity's state
        Action * _current;
};

#endif // ENTITY_H_
