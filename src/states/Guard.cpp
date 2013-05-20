#include <states/guard.h>
#include <constants.h>

namespace EUSDAB
{
    namespace States
    {
        Guard::Guard():
            State(),
            
        {
        }

        Guard::~Guard()
        {
        }

        void Guard::onUp(const Event & e)
        {
            State::onUp(e);
            
        }

        void Guard::onDown(const Event & e)
        {
            State::onDown(e);
            
        }

        void Guard::onLeft(const Event & e)
        {
            State::onLeft(e);
            
        }

        void Guard::onRight(const Event & e)
        {
            State::onRight(e);
            
        }
        
        void Guard::onA(const Event & e)
        {
            State::onA(e);
            
        }
        
        void Guard::onB(const Event & e)
        {
            State::onB(e);
            
        }
        
        void Guard::onTrigger(const Event & e)
        {
            State::onTrigger(e);
            if (e.edge == Event::FallingEdge)
            {
                switchState(Movement::Idle | _mvt.direction());
            }
            
        }
        
        void Guard::onAnimationEnd()
        {
            State::onAnimationEnd();
            Movement newMvt(_mvt);
            newMvt.setAction(Movement::Shield);
            switchState(newMvt);
        }
        

        void Guard::onNextFrame()
        {
            State::onNextFrame();

            
            
        }
        
        void Guard::onEnter()
        {
            State::onEnter();
        }
        
        
        void Guard::onLeave()
        {
            State::onLeave();
        }
        
    }
}
