#include <states/crouch.h>
#include <character.h>

namespace CharacterStates
{
    Crouch::Crouch(Character & c, DirectionX dirX, DirectionY dirY):
        BaseState(c, dirX, dirY)
    {
    }

    Crouch::~Crouch()
    {
    }

    void Crouch::enter()
    {
        BaseState::enter();
    }

    void Crouch::update()
    {
        BaseState::update();
        const Joystick::State & j = _character.joystickState();
        if (j.axisPosition(Joystick::Y) > 0) // get up
        {
            if (isDirection(Right))
            {
                _character.state(BaseState::IdleRight);
            }
            else
            {
                _character.state(BaseState::IdleLeft);
            }
        }
        else if (isDirection(Right))
        {
            if (j.axisPosition(Joystick::X) < 0) // joystick to the left, change direction
            {
                _character.state(BaseState::CrouchLeft);
            }
        }
        else
        {
            if (j.axisPosition(Joystick::X) > 0) // joystick to the right, change direction
            {
                _character.state(BaseState::CrouchRight);
            }
        }
    }

    void Crouch::leave()
    {
        BaseState::leave();
    }
}
