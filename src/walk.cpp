//-------------walk.cpp
#include <walk.h>
#include <character.h>

Walk(Character &c, float speed):
	CharacterState(c)
{
	if(isDirection(Right))
	{
		_motion.x = speed;
		_motion.y = 0.f;
	}
	else
	{
		_motion.x = -speed;
		_motion.y = 0.f;
	}
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
	if (x * _motion.x = 0)
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
	else if (x * _motion.x < 0)
	{
		// joystick dans le sens contraire, il faut changer d'etat.
		if (isDirection(Right))
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
		if (sf::Joystick::isButtonPressed(_character.joystickId(), BUTTON_A))
		{
			if (isDirection(Left))
			{
				_character.state(CharacterState::AttackLeft);
			}
			else
			{
				_character.state(CharacterState::AttackRight);
			}
		}
		else if (sf::Joystick::isButtonPressed(_character.joystickId(), BUTTON_B))
		{
			if (isDirection(Left))
			{
				_character.state(CharacterState::SpecialLeft);
			}
			else
			{
				_character.state(CharacterState::SpecialRight);
			}
		}
	}
}

void Walk::leave()
{

}
