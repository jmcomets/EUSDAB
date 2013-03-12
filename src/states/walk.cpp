#include <states/walk.h>
#include <character.h>

namespace CharacterStates
{
    Walk::Walk(Character &c, float speed, DirectionX dirX, DirectionY dirY):
        BaseState(c, dirX, dirY)
    {
        if (isDirection(Right))
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

    Walk::~Walk()
    {
    }

    void Walk::enter()
    {
        BaseState::enter();
    }

    void Walk::update()
    {
        BaseState::update();
        const Joystick::State & j = _character.joystickState();
        if (j.axisPosition(Joystick::Axis::X) * _motion.x == 0.)
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
        else if (j.axisPosition(Joystick::Axis::X) * _motion.x < 0)
        {
            // joystick dans le sens contraire, il faut changer d'etat.
            if (isDirection(Left))
            {
                _character.state(BaseState::WalkRight);
            }
            else
            {
                _character.state(BaseState::WalkLeft);
            }
        }
        else
        {
            _character.move(_motion);
            /*if (j.isButtonFront(_character.joystickId(), BUTTON_A))
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
            else if (j.isButtonFront(_character.joystickId(), BUTTON_B))
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

    void Walk::leave()
    {
        BaseState::leave();
    }
}
