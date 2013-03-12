#include <states/run.h>
#include <character.h>

namespace CharacterStates
{
    Run::Run(Character & c, float speed, DirectionX dirX, DirectionY dirY) :
        BaseState(c, dirX, dirY)
    {
        if(isDirection(Right))
        {
            _motion.x = speed;
            _motion.y = 0.f;
        }
        else
        {
            _motion.x = -speed;
            _motion.y = 0.f;
        }
    }

    Run::~Run()
    {
    }

    void Run::enter()
    {
        BaseState::enter();
    }

    void Run::update()
    {
        BaseState::update();
        const Joystick::State & j = _character.joystickState();
        if (j.axisPosition(Joystick::X) * _motion.x == 0.)
        {
            if (isDirection(Right))
            {
                _character.state(BaseState::IdleRight);
            }
            else
            {
                _character.state(BaseState::IdleLeft);
            }
        }
        else if (j.axisPosition(Joystick::X) * _motion.x < 0)
        {
            if (isDirection(Left))
            {
                _character.state(BaseState::RunRight);
            }
            else
            {
                _character.state(BaseState::RunLeft);
            }
        }
        else
        {
            _character.move(_motion);
            /*if (j.isButtonFront(Joystick::ButtonA)) 
            {
                if (isDirection(Left))
                {
                    _character.state(BaseState::AttackLeft);
                }
                else
                {
                    _character.state(BaseState::AttackRight);
                }
            }
            else if (j.isButtonFront(Joystick::ButtonB))
            {
                if (isDirection(Left))
                {
                    _character.state(BaseState::SpecialLeft);
                }
                else
                {
                    _character.state(BaseState::SpecialRight);
                }
            }*/
        }
    }

    void Run::leave()
    {
        BaseState::leave();
    }
}
