#include <jump1.h>

static const int halfJump = 50; // this const permit to to know the half of a jump
static const int jumpSpeed = 100; // this const permit to regulate the height of a jump


Jump1::Jump1(Character & c, DirectionX dirX, DirectionY dirY):
	CharacterState(c, dirX, dirY)
{
    _motion.x = 0;
    _motion.y = jumpSpeed;
}

Jump1::~Jump1()
{
}

void Jump1::enter()
{
	CharacterState::enter();
	float x = _character.joystickState().axisPosition(Joystick::X);
	_motion.x=x;
    _motion.y=jumpSpeed;
}

void Jump1::update()
{
	CharacterState::update();
    const Joystick::State & j = _character.joystickState();
	float x = j.axisPosition(Joystick::X);
	float y = j.axisPosition(Joystick::Y);
	bool frontY = j.isAxisFront(Joystick::Y);

	_motion.x = x; // set the x movement value

	// direction down to break a jump
	if (frontY && y < 0)
	{
		if (isDirection(Left))
		{
			_character.state(CharacterState::FallingLeft);
		}
		else
		{
			_character.state(CharacterState::FallingRight);
		}
	}	// joystick in the opposite direction, need to change the state to face the opposite direction
	else if (x*_motion.x < 0)
	{
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
		if (j.isButtonDown(TriggerLeft) || j.isButtonDown(TriggerRight)
		{
			if (isDirection(Left))
			{
				_character.state(CharacterState::AerialDodgeLeft);
			}
			else
			{
				_character.state(CharacterState::AerialDodgeRight);
			}
		}
		else if (j.isButtonDown(ButtonA))
		{
			if (isDirection(Left))
			{
				_character.state(CharacterState::AerialAttackLeft);
			}
			else
			{
				_character.state(CharacterState::AerialAttackRight);
			}
		}
		else if (j.isButtonDown(ButtonB))
		{
			if (isDirection(Left))
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

void Jump1::leave()
{
	CharacterState::leave();
}
