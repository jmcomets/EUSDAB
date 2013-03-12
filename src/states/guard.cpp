#include <states/guard.h>
#include <character.h>

namespace CharacterStates
{
    Guard::Guard(Character & c, DirectionX dirX, DirectionY dirY):
         BaseState(c, dirX, dirY)
    {
    }

    Guard::~Guard()
    {
    }

    void Guard::enter()
    {
        BaseState::enter();
    }

    void Guard::leave()
    {
        BaseState::leave();
    }

    void Guard::update()
    {
        BaseState::update();

        // Decrase the shield
        _character.decreaseShieldCapacity();

        const Joystick::State & j = _character.joystickState();
        float x = j.axisPosition(Joystick::X);
        bool frontX = j.isAxisFront(Joystick::X);

        // If the shield is broken
        if (_character.shieldCapacity() < 1)
        {
            if (isDirection(Left))
            {
                _character.state(BaseState::StunnedLeft);
            }
            else
            {
                _character.state(BaseState::StunnedRight);
            }

        }
        else if (j.isButtonDown(Joystick::TriggerLeft) == false
                || j.isButtonDown(Joystick::TriggerRight) == false)
        {
            if (isDirection(Left))
            {
                _character.state(BaseState::IdleLeft);
            }
            else
            {
                _character.state(BaseState::IdleRight);
            }
        }

        else if (x != 0. && frontX)
        {
            if (isDirection(Left))
            {
                _character.state(BaseState::DodgeLeft);
            }
            else
            {
                _character.state(BaseState::DodgeRight);
            }
        }
    }
}
