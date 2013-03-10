#ifndef EJECTED_H_
#define EJECTED_H_

#include <states/baseState.h>

namespace CharacterStates
{
    class Ejected: public CharacterState
    {
        public:
            Ejected(Character &);
            Ejected(const Ejected &);
            Ejected(Ejected &&);
            virtual ~Ejected();
            Ejected & operator=(const Ejected &);
            virtual void enter();
            virtual void leave();
            virtual void update();
    };
}

#endif
