#ifndef IDLE_H_
#define IDLE_H_

#include <states/baseState.h>

namespace CharacterStates
{
    class Idle: public BaseState
    {
        public:
            Idle(Character &);
            Idle(const Idle &);
            Idle(Idle &&);
            virtual ~Idle();
            Idle & operator=(const Idle &);
            virtual void enter();
            virtual void leave();
            virtual void update();
    
        private:
            void updateDelay();
            bool _delay;
            unsigned int _frameCounter;
    };
}

#endif
