#ifndef ACTION_H_
#define ACTION_H_

class Entity;

class Action
{
    public:
        // Default constructor
        Action();

        // Value constructor
        Action(Entity &, View &&);

        // Move constructor
        Action(Action &&);

        // Copy constructor
        Action(const Action &);

        // Destructor (non virtual)
        /* virtual */ ~Action();

        // Assignment operator
        Action & operator=(const Action &);

        // Get the view
        View & view();

        // Get the entity
        Entity & entity();

    private:
        View _view;
        Entity & _entity;
};

#endif // ACTION_H_
