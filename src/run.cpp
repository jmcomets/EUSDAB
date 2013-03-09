//-----------------run.cpp
#include <run.h>
#include <character.h>

Run(Character &c, float speed):
	CharacterState(c)
{
	if(isDirection(RIGHT))
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

~Run()
{
}

void Run::enter()
{
	CharacterState::enter();
}

void Run::update()
{
	CharacterState::update();
	float x = sf::JoystickgetAxisposition(_character.joystickId(), sf::Joystick::X);
	if (x * _motion.x = 0)
	{
		if (isDirection(RIGHT))
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
		if(isDirection(RIGHT))
		{
			_character.state(CharacterState::RunRight);
		}
		else
		{
			_character.state(CharacterState::RunLeft);
		}
	}
	else
	{
		_character.move(_motion);
		if (sf::Joystick::isButtonPressed(_character.joystickId(), BUTTON_A))
		{
			if (isDirection(LEFT))
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
			if (isDirection(LEFT))
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

void Run::leave()
{
}
