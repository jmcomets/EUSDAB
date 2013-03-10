#include <states/idle.h>
#include <character.h>

namespace CharacterStates
{
    Idle::Idle(Character & c):
        BaseState(c), _delay(false)
    {
    }

    Idle::~Idle()
    {
    }

    void Idle::enter()
    {
        BaseState::enter();
        _delay = false;
    }

    void Idle::leave()
    {
        BaseState::leave();
    }

    void Idle::update()
    {
        BaseState::update();

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
                    _character.state(BaseState::GuardLeft);
                }
                else
                {
                    _character.state(BaseState::GuardRight);
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
}
