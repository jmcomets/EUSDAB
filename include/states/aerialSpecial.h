#ifndef AERIAL_SPECIAL_H_
#define AERIAL_SPECIAL_H_

#include <states/baseState.h>

namespace CharacterStates
{
    class AerialSpecial: public CharacterState
    {
        public:
            AerialSpecial(Character &);
            AerialSpecial(const AerialSpecial &);
            AerialSpecial(AerialSpecial &&);
            virtual ~AerialSpecial();
            AerialSpecial & operator=(const AerialSpecial &);
            virtual void enter();
            virtual void leave();
            virtual void update();
    };
}

#endif
