#include <character.h>
#include <stdexcept>

Character::Character():
    _currentState(), _damage(0)
{
}

Character::~Character()
{
}

void Character::update(const JoystickState & joystickState)
{
    CharacterState * oldState = _currentState;
    _currentState->update(joystickState);
    if (oldState != _currentState)
    {
        if (oldState != nullptr)
        {
            _currentState->leave();
        }
        _currentState->enter();
    }
}

void Character::render(Graphics::Target & target, Graphics::RenderStates renderStates)
{
    //trans.translate(_position);
    //_currentState->view().graphics.draw(target, trans);
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
        std::string e = "State id n°: ";
        e += id + "doesn't exist for " + _name;
        throw std::runtime_error(e);
    }
}

std::string const & Character::name()
{
    return _name;
}

void Character::name(std::string const & name)
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

unsigned int Character::joystickId()
{
    return _joystickId;
}

void Character::joystickId(unsigned int joystickId)
{
    _joystickId = joystickId;
}

