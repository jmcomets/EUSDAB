#include <run.h>
#include <character.h>

Run::Run(Character & c, float speed, DirectionX dirX, DirectionY dirY) :
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

Run::~Run()
{
}

void Run::enter()
{
    CharacterState::enter();
}

void Run::update()
{
    CharacterState::update();
    const Joystick::State & j = _character.joystickState();
    if (j.axisPosition(Joystick::X) * _motion.x == 0)
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
    else if (j.axisPosition(Joystick::X) * _motion.x < 0)
    {
        if (isDirection(Left))
        {
            _character.state(CharacterState::RunRight);
        }
        else
        {
            _character.state(CharacterState::RunLeft);
        }
    }
    else
    {
        _character.move(_motion);
        /*if (j.isButtonFront(Joystick::ButtonA)) 
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
        else if (j.isButtonFront(Joystick::ButtonB))
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

void Run::leave()
{
}
