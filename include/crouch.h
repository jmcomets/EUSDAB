#ifndef CROUCH_H_
#define CROUCH_H_

#include <characterState.h>

class Crouch: public CharacterState
{
    public:
        Crouch(Character &, DirectionX, DirectionY);
        Crouch(const Crouch &);
        Crouch(Crouch &&);
        virtual ~Crouch();
        Crouch & operator=(const Crouch &);
        virtual void enter();
        virtual void leave();
        virtual void update(const JoystickState &);
};

#endif
