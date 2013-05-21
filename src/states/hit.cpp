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

        Hit::~Hit()
        {
        }

        void Hit::onUp(const Event & e)
        {
            State::onUp(e);
        }

        void Hit::onDown(const Event & e)
        {
            State::onDown(e);
        }

        void Hit::onLeft(const Event & e)
        {
            State::onLeft(e);
        }

        void Hit::onAnimationEnd()
        {
            std::cout << "Coucou, tu veux voir ma ..." << std::endl;
            State::onAnimationEnd();
            Movement newMvt(_mvt);
            newMvt.setAction(Movement::Idle);
            switchState(newMvt);
        }

        void Hit::onRight(const Event & e)
        {
            State::onRight(e);

        }

        void Hit::onNextFrame()
        {
            State::onNextFrame();
        }
    }
}
