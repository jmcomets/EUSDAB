#ifndef LANDING_H_
#define LANDING_H_

#include <states/baseState.h>

namespace CharacterStates
{
    class Landing: public CharacterState
    {
        public:
            Landing(Character &);
            Landing(const Landing &);
            Landing(Landing &&);
            virtual ~Landing();
            Landing & operator=(const Landing &);
            virtual void enter();
            virtual void leave();
            virtual void update();
    };
}

#endif
