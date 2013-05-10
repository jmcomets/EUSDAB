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
            Listener::onNextFrame();
            bool animationEnd=false;
            if (_animation != nullptr)
            {
                animationEnd=_animation->advance();
            }
            if (animationEnd)
            {
                if (_mvt.flag() & Movement::Left)
                {
                    switchState(Movement::Idle | Movement::Left);
                }
                else if (_mvt.flag() & Movement::Right)
                {
                    switchState(Movement::Idle | Movement::Right);
                }
                else
                {
                    switchState(Movement::Idle | Movement::Left);
                } 
            }  
        }
        
        void Special::onEnter()
        {
        
        }
        
        void Special::onLeave()
        {
            
        }
        
      
    }
}
