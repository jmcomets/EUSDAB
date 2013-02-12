#ifndef ACTION_H_
#define ACTION_H_

class Entity;

class Action
{
    public:
        Action(Entity &);
        virtual ~Action();

    private:
        Entity & _entity;
};

#endif // ACTION_H_
