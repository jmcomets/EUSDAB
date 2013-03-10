#include <states/smash.h>
#include <character.h>

namespace CharacterStates
{
    Smash::Smash(Character & c, DirectionX dirX, DirectionY dirY, const unsigned int duration):
        BaseState(c, dirX, dirY)
    {
        countdown = duration;
    }

    Smash::~Smash()
    {
    }

    void Smash::enter()
    {
        BaseState::enter();
    }

    void Smash::update()
    {
        BaseState::update();
        if (--countdown == 0)
        {
            if (isDirection(Right))
            {
                _character.state(IdleRight);
            }
            else
            {
                _character.state(IdleLeft);
            }
        }
    }

    void Smash::leave()
    {
    }
}
