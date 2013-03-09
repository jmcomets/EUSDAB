#include <walk.h>
#include <character.h>

Walk::Walk(Character &c, float speed, DirectionX dirX, DirectionY dirY):
    CharacterState(c, dirX, dirY)
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

Walk::~Walk()
{
}

void Walk::enter()
{
    CharacterState::enter();
}

void Walk::update()
{
    CharacterState::update();
    const Joystick::State & j = _character.joystickState();
    if (j.axisPosition(Joystick::Axis::X) * _motion.x == 0)
    {
        if (isDirection(Right))
        {
            _character.state(CharacterState::IdleRight);
        }
        else
        {
            _character.state(CharacterState::IdleLeft);
        }
    }
    else if (j.axisPosition(Joystick::Axis::X) * _motion.x < 0)
    {
        // joystick dans le sens contraire, il faut changer d'etat.
        if (isDirection(Left))
        {
            _character.state(CharacterState::WalkRight);
        }
        else
        {
            _character.state(CharacterState::WalkLeft);
        }
    }
    else
    {
        _character.move(_motion);
        /*if (j.isButtonFront(_character.joystickId(), BUTTON_A))
        {
            if (isDirection(Left))
            {
                _character.state(CharacterState::AttackLeft);
            }
            else
            {
                _character.state(CharacterState::AttackRight);
            }
        }
        else if (j.isButtonFront(_character.joystickId(), BUTTON_B))
        {
            if (isDirection(Left))
            {
                _character.state(CharacterState::SpecialLeft);
            }
            else
            {
                _character.state(CharacterState::SpecialRight);
            }
        }*/
    }
}

void Walk::leave()
{

}
