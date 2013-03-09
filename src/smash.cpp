#include <smash.h>

Smash::Smash(Character & c, DirectionX dirX, DirectionY dirY, const unsigned int duration):
	CharacterState(c, dirX, dirY)
{
	countdown = duration;
}

Smash::~Smash()
{
}

void Smash::enter()
{
	CharacterState::enter();
}

void Smash::update()
{
	CharacterState::update();
	if (--countdown == 0)
	{
		if (isDirection(Right))
		{
			_character.state(IdleRight);
		}
		else
		{
			_character.state(IdleLeft);
		}
	}
}

void Smash::leave()
{
}
