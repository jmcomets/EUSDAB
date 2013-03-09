//-------------jump1.cpp
#include <jump1.h>

static const halfjump;//this const permit to


Jump1(&Character c, float speedx, float speedy):
	CharacterState(), 
{
    if(isDirection(RIGHT))
    {
        _motion.x = speedx;
		_motion.y = speedy;
    }
    else
    {
        _motion.x = -speedx;
		_motion.y = speedy;
    }
}

~Jump1()
{
}

void Jump1::enter()
{
	CharacterState::enter();
}

void Jump1::update()
{
	CharacterState::update();
	float x = sf::Joystick::getAxisPosition(_character.joystickId(), sf::Joystick::X);
	float y = sf::Joystick::getAxisPosition(_character.joystickId(), sf::Joystick::Y);
	if (y < 0)
	{
		// direction down to break a jump 
		if (isDirection(Left))
		{
			_character.state(CharacterState::FallingLeft);
		}
		else
		{
			_character.state(CharacterState::FallingRight);
		}
	}	
	else if (x*_motion.x < 0)
	{
		// joystick in the opposite direction, need to change the state to face the opposite direction
		if (isDirection(Left))
		{
			_character.state(CharacterState::Jump1Right);
		}
		else
		{
			_character.state(CharacterState::Jump1Left);
		}
	}
	/*else
	{
		_character.move(_motion);
		if (sf::Joystick::isButtonPressed (_character.joystickId(), BUTTON_A))
		{
			if (_motion.x < 0)
			{
				_character.state(CharacterState::AerialAttackLeft);
			}
			else
			{
				_character.state(CharacterState::AerialAttackRight);
			}
		}
		else if (sf::Joystick::isButtonPressed (_character.joystickId(), BUTTON_B))
		{
			if (_motion.x < 0)
			{
				_character.state(CharacterState::AerialSpecialLeft);
			}
			else
			{
				_character.state(CharacterState::AerialSpecialRight);
			}
		}
	}*/
}

void Walk::leave()
{

}
