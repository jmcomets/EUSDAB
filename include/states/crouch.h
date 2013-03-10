#ifndef CROUCH_H_
#define CROUCH_H_

#include <states/baseState.h>

namespace CharacterStates
{
    class Crouch: public BaseState
    {
        public:
            Crouch(Character &, DirectionX, DirectionY);
            Crouch(const Crouch &);
            Crouch(Crouch &&);
            virtual ~Crouch();
            Crouch & operator=(const Crouch &);
            virtual void enter();
            virtual void leave();
            virtual void update();
    };
}

#endif
