#include <character.h>
#include <stdexcept>

Character::Character():
    Entity(),
    _joystickState(0), _currentState(nullptr), 
    _states(), _name(), _damage(0)
{
}

Character::~Character()
{
}

void Character::update()
{
    CharacterState * oldState = _currentState;
    _currentState->update();
    if (oldState != _currentState)
    {
        if (oldState != nullptr)
        {
            _currentState->leave();
        }
        _currentState->enter();
    }
}

void Character::render(Graphics::Target &, Graphics::RenderStates)
{
    //trans.translate(_position);
    //_currentState->view().graphics.draw(target, trans);
}

inline void Character::addState(CharacterState::Id id, CharacterState * charState)
{
    _states[id] = charState;
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

inline std::string const & Character::name()
{
    return _name;
}

inline void Character::name(std::string const & n)
{
    _name = n;
}

inline int Character::damage()
{
    return _damage;
}

inline void Character::damage(int d)
{
    _damage = d;
}

inline const Joystick::State & Character::joystickState() const
{
    return _joystickState;
}
