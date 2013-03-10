#include <states/jump.h>
#include "character.h"

namespace CharacterStates
{
    static const int halfJump = 50; // this const permit to to know the half of a jump
    static const int jumpSpeed = 100; // this const permit to regulate the height of a jump

    Jump::Jump(Character & c, DirectionX dirX, DirectionY dirY, unsigned int jumpNbr, unsigned int jumpNbrMax):
        BaseState(c, dirX, dirY)
    {
        _motion.x = 0;
        _motion.y = jumpSpeed;
        jumpNumber=jumpNbr;
        jumpNumber=jumpNbrMax;
        FrameCounter=0;
        
    }

    Jump::~Jump()
    {
    }

    void Jump::enter()
    {
        BaseState::enter();
        float x = _character.joystickState().axisPosition(Joystick::X);
        _motion.x=x;
        _motion.y=jumpSpeed;
        frameCounter=0;
    }

    void Jump::update()
    {
        BaseState::update();
        const Joystick::State & j = _character.joystickState();
        float x = j.axisPosition(Joystick::X);
        float y = j.axisPosition(Joystick::Y);
        bool frontY = j.isAxisFront(Joystick::Y);

        _motion.x = x; // set the x movement value

        
        // joystick in the opposite direction, need to change the state to face the opposite direction
        else if (x*_motion.x < 0)
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
        if (frontY && y < 0)
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
        else if ((j.isBouttonDown(BouttonX)&&j.isBouttonFront(BouttonX))
                    ||(j.isBouttonDown(BouttonY)&&j.isBouttonFront(BouttonY))
                    ||(frontY && y < 0)) 
        {
            if ((jumpNumber<(jumpNumberMax))&&(FrameCounter>halfJump))
            {
                jumpNumber++;
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
        /*if ((j.isButtonDown(TriggerLeft)&&j.isBouttonFront(TriggerLeft))
                || (j.isButtonDown(TriggerRight)&&j.isBouttonFront(Triggeright)))
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
        else if (j.isButtonDown(ButtonA)&&j.isBouttonFront(BouttonA))
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
        else if (j.isButtonDown(ButtonB)&&j.isBouttonFront(BouttonB))
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
            frameCounter++;
        }
    }

    void Jump::leave()
    {
        BaseState::leave();
    }
}

