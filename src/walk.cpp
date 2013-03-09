//-------------walk.cpp
#include <walk.h>

Walk(&Character c, float speed):
	CharacterState(),  _motion(speed, 0)
{
}

~Walk()
{
}

void Walk::enter()
{
	CharacterState::enter();
}

void Walk::update()
{
	CharacterState::update();
	float x = sf::Joystick::getAxisPosition(_character.joystickId, sf::Joystick::X);
	if (x*_motion.x = 0)
	{
		if (_motion.x > 0)
		{
			_character.state(IdleRight);
		}
		else
		{
			_character.state(IdleLeft);
		}
	}
	else if (x*_motion.x < 0)
	{
		// joystick dans le sens contraire, il faut changer d'etat.
		if (_motion.x < 0)
		{
			_character.state(WalkRight);
		}
		else
		{
			_character.state(WalkLeft);
		}
	}
	else
	{
		_character.move(_motion);
	}
}

void Walk::leave()
{

}
