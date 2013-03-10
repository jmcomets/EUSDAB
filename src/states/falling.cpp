#include <states/falling.h>
#include <states/jump.h>
#include <character.h>
#include <stdexcept>

namespace CharacterStates
{
    static const int halffalling = 50; // this const permit to to know the half of a falling
    static const int fallingSpeed = 100; // this const permit to regulate the height of a falling

    Falling::Falling(Character & c, DirectionX dirX, DirectionY dirY):
        BaseState(c, dirX, dirY)
    {
        _motion.x = 0;
        _motion.y = fallingSpeed;        
    }

    Falling::~Falling()
    {
    }

    void Falling::enter()
    {
        BaseState::enter();
        float x = _character.joystickState().axisPosition(Joystick::X);
        _motion.x=x;
        _motion.y=fallingSpeed;
    }

    void Falling::update()
    {
        BaseState::update();
        const Joystick::State & j = _character.joystickState();
        float x = j.axisPosition(Joystick::X);
        float y = j.axisPosition(Joystick::Y);
        bool frontY = j.isAxisFront(Joystick::Y);

        _motion.x = x; // set the x movement value

        if (_character.isFlying() == false)
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
                _character.state(BaseState::FallingRight);
            }
            else
            {
                _character.state(BaseState::FallingLeft);
            }
        }

        //consecutive to start a new jump
        else if ((j.isButtonDown(Joystick::ButtonX)&&j.isButtonFront(Joystick::ButtonX))
                    ||(j.isButtonDown(Joystick::ButtonY)&&j.isButtonFront(Joystick::ButtonY))
                    ||(frontY && y < 0)) 
        {
            Jump * jumpState = dynamic_cast<Jump *>(_character.previousState());
            if (jumpState != nullptr)
            {
                if (jumpState->jumpNumber() < jumpState->jumpNumberMax())
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
            else
            {
                throw std::runtime_error("Falling state entered from weird state");
            }
        }
        //dodge
        /*if ((j.isButtonDown(Joystick::TriggerLeft)&&j.isButtonFront(Joystick::TriggerLeft))
                || (j.isButtonDown(Joystick::TriggerRight)&&j.isButtonFront(Joystick::Triggeright)))
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
        }
    }

    void Falling::leave()
    {
        BaseState::leave();
    }
}

