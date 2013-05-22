#include <states/hit.h>
#include <iostream>

namespace EUSDAB
{
    namespace States
    {
        Hit::Hit(Movement const & m):
            State(m)
        {
        }

        void Hit::onAnimationEnd()
        {
            State::onAnimationEnd();
            Movement newMvt(_mvt);
            newMvt.setAction(Movement::Idle);
            switchState(newMvt);
        }

        void Hit::onEnter()
        {
            State::onEnter();
            if(_entity != nullptr)
            {
                _entity->setAttackable(false);
            }
        }

        void Hit::onLeave()
        {
            State::onLeave();
            if(_entity != nullptr)
            {
                _entity->setAttackable(true);
            }
        }

        void Hit::onNextFrame()
        {
            State::onNextFrame();
            if(_entity != nullptr && _time > 5)
            {
                _entity->setAttackable(false);
            }
        }
    }
}
