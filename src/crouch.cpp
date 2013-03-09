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

void Walk::update()
{
	CharacterState::update();
	float y = sf::Joystick::getAxisPosition(_character.joystickId(), sf::Joystick::Y);
	float x = sf::Joystick::getAxisPosition(_character.joystickId(), sf::Joystick::X);
	if (y > 0) //get up
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
		if (x < 0) //joystick to the left, change direction
		{
			_character.state(CharacterState::CrouchLeft);
		}
	}
	else
	{
		if (x > 0) //joystick to the right, change direction
		{
			_character.state(CharacterState::CrouchRight);
		}
	}
}

void Crouch::leave()
{
}
