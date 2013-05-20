#include <states/shield.h>
#include <constants.h>

namespace EUSDAB
{
    namespace States
    {
        Shield::Shield():
            State(),
            _curValue(100)
            _maxValue(100);
            _nbrShieldstate(3);
            _regenSpeed(5);
            _decreaseSpeed(5);
            _leaveTime(0);
        {
        }

        Shield::~Shield()
        {
        }

        void Shield::onUp(const Event & e)
        {
            State::onUp(e);
            
        }

        void Shield::onDown(const Event & e)
        {
            State::onDown(e);
            
        }

        void Shield::onLeft(const Event & e)
        {
            State::onLeft(e);
            
        }

        void Shield::onRight(const Event & e)
        {
            State::onRight(e);
            
        }
        
        void Shield::onA(const Event & e)
        {
            State::onA(e);
            
        }
        
        void Shield::onB(const Event & e)
        {
            State::onB(e);
            
        }
        
        void Shield::onTrigger(const Event &)
        {
            State::onTrigger(e);
            if (e.edge == Event::FallingEdge)
            {
                switchState(Movement::Idle | _mvt.direction());
            }
            
        }

        void Shield::onNextFrame()
        {
            State::onNextFrame();

            
            _curValue-=abs(_decreaseSpeed);
            if (_curValue>0)
            {
                changeImage();
            }
            else
            {
                switchState(Movement::Stunned | _mvt.direction());
                _curValue=trunc(_maxValue/2);
            }
            
        }
        
        void Shield::onEnter()
        {
           // State::onEnter();
            calcShieldValue()
            changeImage();
        }
        
        void Shield::changeImage()
        {
            unsigned int num_img=trunc(abs(_curValue/(_maxValue/_nbrShieldstate)));
             _animation->setCurrentFrame(num_img);
        }
        
        void Shield::onLeave()
        {
            State::onLeave();
            _leaveTime=_time;
        }
        
        void Shield::calcShieldValue()
        {
            unsigned int diff=_time-_leaveTime;
            _curValue=abs(diff*_regenSpeed);
            if (_curValue>_maxValue)
            {
                _curValue=_maxValue;
            }
        }
    }
}
