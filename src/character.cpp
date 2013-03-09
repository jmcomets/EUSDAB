#include <character.h>

Character::Character():
    _currentState()
{
}

Character::~Character()
{
}

void Character::update(const Input & input)
{
    CharacterState * oldState = _currentState;
    _currentState->update(input);
    if (oldState != _currentState)
    {
        if (oldState != nullptr)
        {
            _currentState->leave();
        }
        _currentState->enter();
    }
}

void Character::render(Graphics::Target & target, Graphics::Transformation trans)
{
    trans.translate(_position);
    _currentState->view().graphics.draw(target, trans);
}

void Character::addState(CharacterState::Id id, CharacterState * state)
{
    _states[id] = state;
}

void Character::state(CharacterState::Id id)
{
    _currentState = _states[id];
}

