#ifndef IDLE_H_
#define IDLE_H_

#include <characterState.h>

class Idle: public CharacterState
{
    public:
        Idle();
        Idle(const Idle &);
        Idle(Idle &&);
        virtual ~Idle();
        Idle & operator=(const Idle &);
        virtual void enter();
        virtual void leave();
        virtual void update(const sf::Input &);
};

#endif
