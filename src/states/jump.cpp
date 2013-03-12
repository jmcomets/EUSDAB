#include <states/jump.h>
#include "character.h"

namespace CharacterStates
{
    constexpr unsigned int halfJump = 50; // this const permit to to know the half of a jump
    constexpr unsigned int jumpSpeed = 100; // this const permit to regulate the height of a jump

    Jump::Jump(Character & c, DirectionX dirX, DirectionY dirY, unsigned int jumpNbrMax, unsigned int jumpNbr=0):
        BaseState(c, dirX, dirY), 
        _motion(0, jumpSpeed),
        _jumpNumber(jumpNbr), _jumpNumberMax(jumpNbrMax),
        _frameCounter(0)
    {
    }

    Jump::~Jump()
    {
    }

    void Jump::enter()
    {
        BaseState::enter();
        float x = _character.joystickState().axisPosition(Joystick::X);
        _motion.x = x; // FIXME
        _motion.y = jumpSpeed;
        _frameCounter = 0;
        _jumpNumber++;
    }

    void Jump::update()
    {
        BaseState::update();
        const Joystick::State & j = _character.joystickState();
        float x = j.axisPosition(Joystick::X);
        float y = j.axisPosition(Joystick::Y);
        bool frontY = j.isAxisFront(Joystick::Y);

        _motion.x = x; // set the x movement value FIXME
        
        // joystick in the opposite direction, need to change the state to face the opposite direction
        if (x*_motion.x < 0)
        {
            if (isDirection(Left))
            {
                _character.state(BaseState::JumpRight);
            }
            else
            {
                _character.state(BaseState::JumpLeft);
            }
        }
        // direction down to break a jump
        else if (frontY && y < 0)
        {
            if (isDirection(Left))
            {
                _character.state(BaseState::FallingLeft);
            }
            else
            {
                _character.state(BaseState::FallingRight);
            }
        }	
        //consecutive jumps
        else if ((j.isButtonDown(Joystick::ButtonX)&&j.isButtonFront(Joystick::ButtonX))
                    ||(j.isButtonDown(Joystick::ButtonY)&&j.isButtonFront(Joystick::ButtonY))
                    ||(frontY && y < 0)) 
        {
            if (_jumpNumber < _jumpNumberMax && _frameCounter > halfJump)
            {
                if (isDirection(Left))
                {
                    _character.state(BaseState::JumpRight);
                }
                else
                {
                    _character.state(BaseState::JumpLeft);
                }
            }
        }
        //dodge
        /*else if ((j.isButtonDown(Joystick::TriggerLeft)&&j.isButtonFront(Joystick::TriggerLeft))
                || (j.isButtonDown(TriggerRight)&&j.isButtonFront(Joystick::TriggerRight)))
        {
            if (isDirection(Left))
            {
                _character.state(BaseState::AerialDodgeLeft);
            }
            else
            {
                _character.state(BaseState::AerialDodgeRight);
            }
        }
        //aerial normal attack to be completed
        else if (j.isButtonDown(Joystick::ButtonA)&&j.isButtonFront(Joystick::ButtonA))
        {
            if (isDirection(Left))
            {
                _character.state(BaseState::AerialAttackLeft);
            }
            else
            {
                _character.state(BaseState::AerialAttackRight);
            }
        }
        //aerial special attack to be completed
        else if (j.isButtonDown(Joystick::ButtonB)&&j.isButtonFront(Joystick::ButtonB))
        {
            if (isDirection(Left))
            {
                _character.state(BaseState::AerialSpecialLeft);
            }
            else
            {
                _character.state(BaseState::AerialSpecialRight);
            }
        }
        */
        else
        {
            _character.move(_motion);
            _frameCounter++;
        }
    }

    void Jump::leave()
    {
        BaseState::leave();
    }

    unsigned int Jump::jumpNumber() const
    {
        return _jumpNumber;
    }

    unsigned int Jump::jumpNumberMax() const
    {
        return _jumpNumberMax;
    }
}

