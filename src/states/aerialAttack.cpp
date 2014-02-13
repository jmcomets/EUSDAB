#include <states/aerialAttack.h>
#include <cmath>
#include <iostream>

namespace EUSDAB
{
    namespace States
    {
        AerialAttack::AerialAttack(Movement const & m):
            State(m)
        {
        }

        AerialAttack::~AerialAttack()
        {
        }

        void AerialAttack::onAnimationEnd()
        {
            State::onAnimationEnd();
            Movement newMvt(_mvt);
            newMvt.setAction(Movement::Falling);
            switchState(newMvt & ~Movement::Up & ~Movement::Down);
        }

        void AerialAttack::onLeave()
        {
            State::onLeave();
            _entity->physics().velocity().y = 0.1f;
        }
    }
}
