#include <states/shield.h>
#include <constants.h>

namespace EUSDAB
{
    namespace States
    {
        Shield::Shield(Movement const & m):
            State(m),
            _curValue(500),
            _maxValue(500),
            _nbrShieldstate(3),
            _regenSpeed(5),
            _decreaseSpeed(3),
            _leaveTime(0)
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
        
        void Shield::onTrigger(const Event & e)
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

            
            _curValue-=_decreaseSpeed;
            if ((_curValue>0) && (_curValue <_maxValue))
            {
                changeImage();
				_animation->refresh();
            }
            else
            {
                switchState(Movement::Idle | _mvt.direction());
                _curValue= static_cast<unsigned int> (trunc(_maxValue/2));
            }
            
        }
        
        void Shield::onEnter()
        {
           // State::onEnter();
            _animation->setPaused(true);
			_animation->setCurrentFrame(0);
			_animation->refresh();
			//calcShieldValue();
            //changeImage();
        }
        
        void Shield::changeImage()
        { 
            unsigned int num_img= static_cast<unsigned int> (trunc(abs(_curValue/(_maxValue/_nbrShieldstate))));
			std::cout<<"num_img : "<<num_img<<std::endl;
             _animation->setCurrentFrame(num_img);
        }
        
        void Shield::onLeave()
        {
            State::onLeave();
            _leaveTime=_time;
        }
        
        void Shield::calcShieldValue()
        {
            unsigned int diff= static_cast<unsigned int> (trunc(abs(_time-_leaveTime)));
            _curValue=abs(diff*_regenSpeed);
            if (_curValue>_maxValue)
            {
                _curValue=_maxValue;
            }
        }
        
        void Shield::setCurValue(unsigned int v)
        {
            _curValue=v;
        }
        
        void Shield::setMaxValue(unsigned int v)
        {
            _maxValue=v;
        }
        
        void Shield::setNbrShieldstate(unsigned int v)
        {
            _nbrShieldstate=v;
        }
        
        void Shield::setRegenSpeed(unsigned int v)
        {
            _regenSpeed=v;
        }
        
        void Shield::setDecreaseSpeed(unsigned int v)
        {
            _decreaseSpeed=v;
        }
    }
}
