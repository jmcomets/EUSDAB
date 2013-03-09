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
	float x = sf::Joystick::getAxisPosition(_character.joystickId(), sf::Joystick::X);
	if (x*_motion.x = 0)
	{
		if (_motion.x > 0)
		{
			_character.state(CharacterState::IdleRight);
		}
		else
		{
			_character.state(CharacterState::IdleLeft);
		}
	}
	else if (x*_motion.x < 0)
	{
		// joystick dans le sens contraire, il faut changer d'etat.
		if (_motion.x < 0)
		{
			_character.state(CharacterState::WalkRight);
		}
		else
		{
			_character.state(CharacterState::WalkLeft);
		}
	}
	else
	{
		_character.move(_motion);
		if (sf::Joystick::isButtonPressed (_character.joystickId(), BUTTON_A))
		{
			if (_motion.x < 0)
			{
				_character.state(CharacterState::AttackLeft);
			}
			else
			{
				_character.state(CharacterState::AttackRight);
			}
		}
		else if (sf::Joystick::isButtonPressed (_character.joystickId(), BUTTON_B))
		{
			if (_motion.x < 0)
			{
				_character.state(CharacterState::SmashLeft);
			}
			else
			{
				_character.state(CharacterState::SmashLeft);
			}
		}
	}
}

void Walk::leave()
{

}
