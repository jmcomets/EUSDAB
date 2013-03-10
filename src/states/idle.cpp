#include <states/idle.h>
#include <character.h>

const unsigned int landinAnimationLength=100;//to be adapted

namespace CharacterStates
{
    Idle::Idle(Character & c, DirectionX, DirectionY):
         BaseState(c, dirX, dirY), _delay(false)
    {
    }

    Idle::~Idle()
    {
    }

    void Idle::enter()
    {
        BaseState::enter();
        _delay = false;
        _frameCounter=landingAnimationLength;
        
    }

    void Idle::leave()
    {
        BaseState::leave();
    }

    void Idle::update()
    {
        BaseState::update();
        _frameCounter--;
         //this means that we were landing and that the animation finished 
         //so we need to go into the idle state
        if (0==_frameCounter)
        {
                if (isDirection(Left))
                {
                    _character.state(BaseState::IdleLeft);
                }
                else
                {
                    _character.state(BaseState::IdleRight);
                }        
        }
        else if (_delay)
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
