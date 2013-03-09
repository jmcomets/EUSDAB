#ifndef AERIAL_HIT_H_
#define AERIAL_HIT_H_

#include <characterState.h>

class AerialHit: public CharacterState
{
    public:
        AerialHit(Character &);
        AerialHit(const AerialHit &);
        AerialHit(AerialHit &&);
        virtual ~AerialHit();
        AerialHit & operator=(const AerialHit &);
        virtual void enter();
        virtual void leave();
        virtual void update(const JoystickState update());
};

#endif
