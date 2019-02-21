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

        void Shield::onDown(const Event & e)
        {
            State::onDown(e);
            if (e.edge == Event::RisingEdge)
            {
                switchState(Movement::Dodge | _mvt.direction() | Movement::Down);
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
            if (_curValue > 0 && _curValue < _maxValue)
            {
                changeImage();
                _animation->refresh();
            }
            else
            {
                switchState(Movement::ShieldBreak | _mvt.direction());
                _curValue= static_cast<unsigned int>(std::trunc(_maxValue/2));
            }

        }

        void Shield::onEnter()
        {
            State::onEnter();
            _maxValue = _entity->_shieldMaxValue;
            _curValue = _entity->_shieldValue;
            _leaveTime = _entity->_shieldLeaveTime;
            _animation->setPaused(true);
            calcShieldValue();
            changeImage();
            _animation->refresh();
        }

        void Shield::changeImage()
        { 
            unsigned int num_img = _nbrShieldstate * _curValue / _maxValue;
            _animation->setCurrentFrame(num_img);
        }

        void Shield::onLeave()
        {
            State::onLeave();
            _leaveTime =_entity->_globalTime;
            _entity->_shieldValue = _curValue;
            _entity->_shieldLeaveTime =_leaveTime;
        }

        void Shield::calcShieldValue()
        {
            unsigned int diff = static_cast<unsigned int>(std::trunc(std::abs(_entity->_globalTime - _leaveTime)));
            _curValue += diff*_regenSpeed;
            if (_curValue > _maxValue)
            {
                _curValue = _maxValue;
            }
        }

        void Shield::setCurValue(unsigned int v)
        {
            _curValue = v;
        }

        void Shield::setMaxValue(unsigned int v)
        {
            _maxValue = v;
        }

        void Shield::setNbrShieldstate(unsigned int v)
        {
            _nbrShieldstate = v;
        }

        void Shield::setRegenSpeed(unsigned int v)
        {
            _regenSpeed = v;
        }

        void Shield::setDecreaseSpeed(unsigned int v)
        {
            _decreaseSpeed = v;
        }
    }
}
