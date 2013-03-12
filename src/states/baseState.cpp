#include <states/baseState.h>
#include <character.h>

namespace CharacterStates
{
    BaseState::BaseState(Character & c, DirectionX dirX, DirectionY dirY):
        _character(c), _direction(dirX, dirY)
    {
    }

    BaseState::~BaseState()
    {
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

    View & BaseState::view()
    {
        return *_view;
    }

    bool BaseState::isDirection(DirectionX x) const
    {
        return _direction.first == x;
    }

    bool BaseState::isDirection(DirectionY y) const
    {
        return _direction.second == y;
    }
}
