#include <states/shield.h>
#include <constants.h>

namespace EUSDAB
{
    namespace States
    {
        Shield::Shield(Movement const & m):
            State(m),
            _curValue(1000),
            _maxValue(1000),
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
            if (e.edge == Event::RisingEdge)
            {
                switchState(Movement::Dodge | _mvt.direction()| Movement::Down);
            }
            
        }

        void Shield::onLeft(const Event & e)
        {
            State::onLeft(e);
            if (e.edge == Event::RisingEdge)
            {
                switchState(Movement::Dodge | Movement::Left);
            }
            
        }

        void Shield::onRight(const Event & e)
        {
            State::onRight(e);
            if (e.edge == Event::RisingEdge)
            {
                switchState(Movement::Dodge | Movement::Right);
            }
            
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
		    _maxValue = _entity->_shieldMaxValue;
		    _curValue = _entity->_shieldValue;
		    _leaveTime= _entity->_shieldLeaveTime;
			std::cout << "enterValue : "<< _entity->_shieldValue << std::endl;
            _animation->setPaused(true);
			calcShieldValue();
            changeImage();
			_animation->refresh();
        }
        
        void Shield::changeImage()
        { 
            unsigned int num_img= static_cast<unsigned int> (trunc(abs(_curValue/(_maxValue/_nbrShieldstate))));
             _animation->setCurrentFrame(num_img);
        }
        
        void Shield::onLeave()
        {
            State::onLeave();
            _leaveTime=_entity->_globalTime;
			std::cout<< "time : " << _leaveTime << "leave Value : " << _curValue << std::endl;
			_entity->_shieldValue = _curValue;
			_entity->_shieldLeaveTime=_leaveTime;
			//Movement::Flag f = Movement::Shield | Movement::Right;
			//State * s = _entity->state(Movement(f));
			//Shield * s2 = dynamic_cast<Shield *>(s);
			//s2->setCurValue(_curValue);
			//f = Movement::Shield | Movement::Left;
			//s = _entity->state(Movement(f));
			//s2 = dynamic_cast<Shield *>(s);
			//s2->setCurValue(_curValue);
        }
        
        void Shield::calcShieldValue()
        {
            unsigned int diff= static_cast<unsigned int> (trunc(abs(_entity->_globalTime-_leaveTime)));
            _curValue+=abs(diff*_regenSpeed);
            if (_curValue>_maxValue)
            {
                _curValue=_maxValue;
            }
			std::cout<< "diff : " << diff*_regenSpeed << "curTime : " << _entity->_globalTime << "leave : "<< _leaveTime<<"shield "<< _curValue<< std::endl;
			std::cout<<"max : "<< _maxValue << std::endl;
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
