#include <character.h>
#include <stdexcept>

constexpr unsigned int shieldCapacityMax = 100;

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
    _joystickState.update();
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

void Character::render(Graphics::Target & target, Graphics::RenderStates states)
{
    states.transform.translate(_pos);
    _currentState->view().graphics->render(target, states);
}

bool Character::addState(BaseState::Id id, BaseState * state)
{
    return _states.insert(std::make_pair(id, state)).second;
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

const std::string & Character::name() const
{
    return _name;
}

const std::string & Character::name(const std::string & n)
{
    return _name = n;
}

int Character::damage() const
{
    return _damage;
}

int Character::damage(int d)
{
    return _damage = d;
}

const Joystick::State & Character::joystickState() const
{
    return _joystickState;
}

const BaseState * Character::currentState() const
{
    return _currentState;
}

const BaseState * Character::previousState() const
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

bool Character::isFlying() const
{
    return _isFlying;
}

bool Character::isFlying(bool aFlying)
{
    return _isFlying = aFlying;
}

unsigned int Character::decreaseShieldCapacity(unsigned int variation)
{
    return _shieldCapacity = std::max(shieldCapacityMax,
            _shieldCapacity - variation);
}

unsigned int Character::incraseShieldCapacity(unsigned int variation)
{
    return _shieldCapacity = std::min(shieldCapacityMax,
            _shieldCapacity + variation);
}

unsigned int Character::shieldCapacity(unsigned int sc)
{
    return _shieldCapacity = std::min(sc, shieldCapacityMax);
}

unsigned int Character::shieldCapacity() const
{
    return _shieldCapacity;
}
