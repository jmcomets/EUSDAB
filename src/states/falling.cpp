#include <states/falling.h>
#include "character.h"

namespace CharacterStates
{
    static const int halffalling = 50; // this const permit to to know the half of a falling
    static const int fallingSpeed = 100; // this const permit to regulate the height of a falling

    falling::falling(Character & c, DirectionX dirX, DirectionY dirY)
        BaseState(c, dirX, dirY)
    {
        _motion.x = 0;
        _motion.y = fallingSpeed;        
    }

    falling::~falling()
    {
    }

    void falling::enter()
    {
        BaseState::enter();
        float x = _character.joystickState().axisPosition(Joystick::X);
        _motion.x=x;
        _motion.y=fallingSpeed;
    }

    void falling::update()
    {
        BaseState::update();
        const Joystick::State & j = _character.joystickState();
        float x = j.axisPosition(Joystick::X);
        float y = j.axisPosition(Joystick::Y);
        bool frontY = j.isAxisFront(Joystick::Y);

        _motion.x = x; // set the x movement value

        if !(_character.isFlying())
        {
            if (isDirection(Left))
            {
                _character.state(BaseState::LandingLeft);
            }
            else
            {
                _character.state(BaseState::LandingRight);
            }
        }
        // joystick in the opposite direction, need to change the state to face the opposite direction
        else if (x*_motion.x < 0)
        {
            if (isDirection(Left))
            {
                _character.state(BaseState::fallingRight);
            }
            else
            {
                _character.state(BaseState::fallingLeft);
            }
        }

        //consecutive to start a new jump
        else if ((j.isButtonDown(ButtonX)&&j.isButtonFront(ButtonX))
                    ||(j.isButtonDown(ButtonY)&&j.isButtonFront(ButtonY))
                    ||(frontY && y < 0)) 
        {
            if (_character.previousState()->jumpNumber
                    <_character.previousState()->jumpNumberMax)
            {
                if (isDirection(Left))
                {
                    _character.state(BaseState::jumpRight);
                }
                else
                {
                    _character.state(BaseState::jumpLeft);
                }
            }
        }
        //dodge
        /*if ((j.isButtonDown(TriggerLeft)&&j.isButtonFront(TriggerLeft))
                || (j.isButtonDown(TriggerRight)&&j.isButtonFront(Triggeright)))
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
        else if (j.isButtonDown(ButtonA)&&j.isButtonFront(ButtonA))
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
        else if (j.isButtonDown(ButtonB)&&j.isButtonFront(ButtonB))
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

    void falling::leave()
    {
        BaseState::leave();
    }
}

