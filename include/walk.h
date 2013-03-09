#ifndef WALK_H_
#define WALK_H_

#include <characterState.h>

class Walk: public CharacterState
{
    public:
        Walk();
        Walk(const Walk &);
        Walk(Walk &&);
        virtual ~Walk();
        Walk & operator=(const Walk &);
        virtual void enter();
        virtual void leave();
        virtual void update(const sf::Input &);
};

#endif
