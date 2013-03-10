#ifndef AERIAL_HIT_H_
#define AERIAL_HIT_H_

#include <states/baseState.h>

namespace CharacterStates
{
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
            virtual void update();
    };
}

#endif
