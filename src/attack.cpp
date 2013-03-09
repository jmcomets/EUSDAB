#include <attack.h>

Attack::Attack(Character & c, DirectionX dirX, DirectionY dirY, const unsigned int duration):
	CharacterState(c, dirX, dirY)
{
	countdown = duration;
}

Attack::~Attack()
{
}

void Attack::enter()
{
	CharacterState::enter();
}

void Attack::update()
{
	CharacterState::update();
	if (--countdown == 0)
	{
		if(isDirection(Right))
		{
			_character.state(IdleRight);
		}
		else
		{
			_character.state(IdleLeft);
		}
	}
}

void Attack::leave()
{
	CharacterState::leave();
}
