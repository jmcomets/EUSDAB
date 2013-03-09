#include <characterState.h>
#include <character.h>

CharacterState::~CharacterState()
{
    delete _view;
}

void CharacterState::enter()
{
}

void CharacterState::update()
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
