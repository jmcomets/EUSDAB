#include <idle.h>

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

void Idle::update()
{
    CharacterState::update();

    if (_delay)
    {
        updateDelay();
    }
    else
    {
        const Joystick::State & j = _character.joystickState();
        if (j.isButtonFront(Joystick::TriggerRight)
                || j.isButtonFront(Joystick::TriggerLeft))
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
        else if (j.axisPosition(Joystick::X) || j.axisPosition(Joystick::Y))
        {
            _delay = true;
        }
    }
}

void Idle::updateDelay()
{
    // TODO
}
