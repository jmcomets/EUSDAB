//-----------------------crouch.cpp
#include <crouch.h>
#include <character.h>

Crouch(Character &c):
	CharacterState(c)
{
}

~Crouch()
{
}

void Crouch::enter()
{
	CharacterState::enter();
}

void Walk::update(j)
{
	CharacterState::update();
	if (j.axisPosition(Y) > 0) //get up
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
		if (j.axisPosition(X) < 0) //joystick to the left, change direction
		{
			_character.state(CharacterState::CrouchLeft);
		}
	}
	else
	{
		if (j.axisPosition(X) > 0) //joystick to the right, change direction
		{
			_character.state(CharacterState::CrouchRight);
		}
	}
}

void Crouch::leave()
{
}
