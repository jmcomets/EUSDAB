#ifndef SMASH_H_
#define SMASH_H_

#include <characterState.h>

class Smash: public CharacterState
{
    public:
        Smash(Character &);
        Smash(const Smash &);
        Smash(Smash &&);
        virtual ~Smash();
        Smash & operator=(const Smash &);
        virtual void enter();
        virtual void leave();
        virtual void update(const JoystickState update());
};

#endif
