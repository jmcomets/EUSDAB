#include <states/attack.h>
#include <iostream>

namespace EUSDAB
{
    namespace States
    {
        Attack::Attack():
            State()
        {
        }

        Attack::~Attack()
        {
        }

        void Attack::onUp(const Event & e)
        {
            State::onUp(e);
        }

        void Attack::onDown(const Event & e)
        {
            State::onDown(e);
        }

        void Attack::onLeft(const Event & e)
        {
            State::onLeft(e);
        }

        void Attack::onRight(const Event & e)
        {
            State::onRight(e); 
        }

        void Attack::onNextFrame()
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
        
        void Attack::onEnter()
        {
            State::onEnter();
        }
        
        void Attack::onLeave()
        {
            State::onLeave();
        }
        
      
    }
}
