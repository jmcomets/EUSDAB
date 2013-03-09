#include <idle.h>

#define TRIGGER_L 0
#define TRIGGER_R 0


Idle::Idle(Character & c):
    CharacterState(c), _delay(false)
{
}

Idle::~Idle()
{
}

void Idle::enter()
{
    CharacterState::enter();
    _delay = false;
}

void Idle::leave()
{
    CharacterState::leave();
}

void Idle::update(const JoystickState & j)
{
    CharacterState::update(j);

    if (_delay)
    {
        updateDelay();
    }
    else
    {
        unsigned int joystickId = _character.joystickId();
        if (sf::Joystick::isButtonPressed(joystickId, TRIGGER_L)
                || sf::Joystick::isButtonPressed(joystickId, TRIGGER_L))
        {
            if (isDirection(Left))
            {
                _character.state(CharacterState::GuardLeft);
            }
            else
            {
                _character.state(CharacterState::GuardRight);
            }
        }
        else if (sf::Joystick::getAxisPosition(joystickId, sf::Joystick::X)
                || sf::Joystick::getAxisPosition(joystickId, sf::Joystick::Y))
        {
            _delay = true;
        }
    }
}

void Idle::updateDelay()
{
}
