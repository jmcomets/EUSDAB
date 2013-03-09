//-----------------------crouch.cpp
#include <crouch.h>
#include <character.h>

Crouch::Crouch(Character &c, DirectionX dirX, DirectionY dirY) :
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

void Crouch::update(const JoystickState & j)
{
    CharacterState::update(j);
    if (j.axisPosition(_character.joystickId(), JoystickState::Axis::Y) > 0) //get up
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
        if (j.axisPosition(_character.joystickId(), JoystickState::Axis::X) < 0) //joystick to the left, change direction
        {
            _character.state(CharacterState::CrouchLeft);
        }
    }
    else
    {
        if (j.axisPosition(_character.joystickId(), JoystickState::Axis::X) > 0) //joystick to the right, change direction
        {
            _character.state(CharacterState::CrouchRight);
        }
    }
}

void Crouch::leave()
{
}
