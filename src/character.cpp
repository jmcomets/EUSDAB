#include <character.h>
#include <stdexcept>

static unsigned int shieldCapacityMax=100;

using namespace CharacterStates;

Character::Character():
    Entity(),
    _joystickState(0),
    _previousState(nullptr), _currentState(nullptr),
    _states(), _name(), _damage(0)
{
}

Character::~Character()
{
}

void Character::update()
{
    _previousState = _currentState;
    _currentState->update();
    if (_previousState != _currentState)
    {
        if (_previousState != nullptr)
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

void Character::addState(BaseState::Id id, BaseState * charState)
{
    _states[id] = charState;
}

void Character::state(BaseState::Id id)
{
    auto it = _states.find(id);
    if (it != _states.end())
    {
        _currentState = it->second;
    }
    else
    {
        std::string e = "state id n°: ";
        e += id + "doesn't exist for " + _name;
        throw std::runtime_error(e);
    }
}

std::string const & Character::name()
{
    return _name;
}

void Character::name(std::string const & n)
{
    _name = n;
}

int Character::damage()
{
    return _damage;
}

void Character::damage(int d)
{
    _damage = d;
}

const Joystick::State & Character::joystickState() const
{
    return _joystickState;
}

BaseState * Character::currentState() const
{
    return _currentState;
}

BaseState * Character::previousState() const
{
    return _previousState;
}

BaseState::Id Character::currentStateId() const
{
    for (auto p : _states)
    {
        if (p.second == _currentState)
        {
            return p.first;
        }
    }
    throw std::runtime_error("Unexpected current character state not in character state list, current state is possibly null");
}

BaseState::Id Character::previousStateId() const
{
    for (auto p : _states)
    {
        if (p.second == _previousState)
        {
            return p.first;
        }
    }
    throw std::runtime_error("Unexpected previous character state not in character state list, previous state is possibly null");
}

void Character::setIsFlying(bool aFlying)
{
    _isflying=aFlying;
}

bool Character::isFlying()
{
    return _isflying;
}

void Character::decraseShieldCapacity(unsigned int variation)
{
    int pass= _shieldCapacity-variation;
    if (pass<0)
        _shieldCapacity=pass;
    else
        _shieldCapacity=0;
}

void Character::incraseShieldCapacity(unsigned int variation)
{
    int pass= _shieldCapacity+variation;
    if (pass<100)
        _shieldCapacity=pass;
    else
        _shieldCapacity=100;
}

unsigned int Character::getShieldCapacity()
{
    return _shieldCapacity;
}
