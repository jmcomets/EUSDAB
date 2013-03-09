#ifndef IDLE_H_
#define IDLE_H_

#include <characterState.h>
#include <character.h>

class Idle: public CharacterState
{
    public:
        Idle(Character &);
        Idle(const Idle &);
        Idle(Idle &&);
        virtual ~Idle();
        Idle & operator=(const Idle &);
        virtual void enter();
        virtual void leave();
        virtual void update();

    private:
        void updateDelay();
        bool _delay;
};

#endif
