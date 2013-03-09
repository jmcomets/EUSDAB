#include <crouch.h>
#include <character.h>

Crouch::Crouch(Character & c, DirectionX dirX, DirectionY dirY):
    CharacterState(c, dirX, dirY)
{
}

Crouch::~Crouch()
{
}

void Crouch::enter()
{
    CharacterState::enter();
}

void Crouch::update()
{
    CharacterState::update();
    const Joystick::State & j = _character.joystickState();
    if (j.axisPosition(Joystick::Y) > 0) // get up
    {
        if (isDirection(Right))
        {
            _character.state(CharacterState::IdleRight);
        }
        else
        {
            _character.state(CharacterState::IdleLeft);
        }
    }
    else if (isDirection(Right))
    {
        if (j.axisPosition(Joystick::X) < 0) // joystick to the left, change direction
        {
            _character.state(CharacterState::CrouchLeft);
        }
    }
    else
    {
        if (j.axisPosition(Joystick::X) > 0) // joystick to the right, change direction
        {
            _character.state(CharacterState::CrouchRight);
        }
    }
}

void Crouch::leave()
{
    CharacterState::leave();
}
