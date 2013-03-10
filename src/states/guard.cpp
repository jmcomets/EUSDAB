#include <states/guard.h>
#include <character.h>

namespace CharacterStates
{
    Guard::Guard(Character & c, DirectionX, DirectionY):
         BaseState(c, dirX, dirY), _delay(false)
    {
    }

    Guard::~Guard()
    {
    }

    void Guard::enter()
    {
        BaseState::enter();
        _delay = false;
        _frameCounter=landingAnimationLength;
        
    }

    void Guard::leave()
    {
        BaseState::leave();
    }

    void Guard::update()
    {
        BaseState::update();
        
        //decrase the shield
        _character.decraseShieldCapacity();
        
        const Joystick::State & j = _character.joystickState(); 
        float x = j.axisPosition(Joystick::X);
        bool frontX = j.isAxisFront(Joystick::X);
        //if the shield is broken
        if (_character.getShieldCapacity()<1);
        {            
                if (isDirection(Left))
                {
                    _character.state(BaseState::StunnedLeft);
                }
                else
                {
                    _character.state(BaseState::StunnedRight);
                }
        
        }
        else if
        {
            if ((!j.isButtonDown(Joystick::TriggerLeft)||(!j.isButtonDown(Joystick::TriggerRight))
            {         
                if (isDirection(Left))
                {
                    _character.state(BaseState::StaticLeft);
                }
                else
                {
                    _character.state(BaseState::staticRight);
                }
            }
        }
        else if
        {
            if ((x!=0)&&frontX)
            {         
                if (isDirection(Left))
                {
                    _character.state(BaseState::DodgeLeft);
                }
                else
                {
                    _character.state(BaseState::DodgeRight);
                }
            }
        }
        
    }

    void Guard::updateDelay()
    {
        // TODO
    }
}
