#ifndef HELPLESS_H_
#define HELPLESS_H_

#include <states/baseState.h>

namespace CharacterStates
{
    class Helpless: public CharacterState
    {
        public:
            Helpless(Character &);
            Helpless(const Helpless &);
            Helpless(Helpless &&);
            virtual ~Helpless();
            Helpless & operator=(const Helpless &);
            virtual void enter();
            virtual void leave();
            virtual void update();
    };
}

#endif
