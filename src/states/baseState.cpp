#include <characterState.h>
#include <character.h>

BaseState::BaseState(Character & c, DirectionX dirX, DirectionY dirY):
    _character(c), _direction(dirX, dirY)
{
}

BaseState::~BaseState()
{
    delete _view;
}

void BaseState::enter()
{
}

void BaseState::update()
{
}

void BaseState::leave()
{
}

bool BaseState::isDirection(DirectionX x) const
{
    return _direction.first == x;
}

bool BaseState::isDirection(DirectionY y) const
{
    return _direction.second == y;
}
