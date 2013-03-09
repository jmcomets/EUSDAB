#include <characterState.h>
#include <character.h>

CharacterState::CharacterState(Character & c, DirectionX dirX, DirectionY dirY):
    _character(c), _direction(dirX, dirY)
{
}

CharacterState::~CharacterState()
{
    delete _view;
}

void CharacterState::enter()
{
}

void update()
{
}

void CharacterState::leave()
{
}

bool CharacterState::isDirection(DirectionX x) const
{
    return _direction.first == x;
}

bool CharacterState::isDirection(DirectionY y) const
{
    return _direction.second == y;
}
