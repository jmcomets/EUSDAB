#include <character.h>

Character::Character():
    _currentState()
{
}

Character::~Character() : _damage(0)
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
    auto it = _states.find(id);
    if(it != _states.end())
    {
        _currentState = _states[id];
    }
    else
    {
        throw std::runtime_error("State id n°: " + id + "doesn't exist for " + _name);
    }
}

string const & Character::name()
{
    return _name;
}

void Character::name(string const & name)
{
    _name = name;
}

int Character::damage()
{
    return _damage;
}

void Character::damage(int damage)
{
    _damage = damage;
}

