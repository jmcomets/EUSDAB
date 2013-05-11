#include <states/special.h>
#include <iostream>

namespace EUSDAB
{
    namespace States
    {
        Special::Special():
            State()
        {
        }

        Special::~Special()
        {
        }

        void Special::onUp(const Event & e)
        {
            State::onUp(e);
        }

        void Special::onDown(const Event & e)
        {
            State::onDown(e);
        }

        void Special::onLeft(const Event & e)
        {
            State::onLeft(e);
        }

        void Special::onRight(const Event & e)
        {
            State::onRight(e); 
        }

        void Special::onNextFrame()
        {
            State::onNextFrame();
        }

        void Special::onAnimationEnd()
        {
            State::onAnimationEnd();
            Movement newMvt(_mvt);
            newMvt.setAction(Movement::Idle);
            switchState(newMvt);
        }
        
        void Special::onEnter()
        {
            State::onEnter();
        }
        
        void Special::onLeave()
        {
            State::onLeave();
        }
        
      
    }
}
