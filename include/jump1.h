#ifndef JUMP1_H_
#define JUMP1_H_

#include <characterState.h>

class Jump1: public CharacterState
{
    public:
        Jump1(Character &);
        Jump1(const Jump1 &);
        Jump1(Jump1 &&);
        virtual ~Jump1();
        Jump1 & operator=(const Jump1 &);
        virtual void enter();
        virtual void leave();
        virtual void update(const JoystickState &);
};

#endif
