#include <states/aerialHit.h>

namespace EUSDAB
{
    namespace States
    {
        AerialHit::AerialHit():
            State()
        {
        }

        AerialHit::~AerialHit()
        {
        }

        void AerialHit::onUp(const Event & e)
        {
            State::onUp(e);
        }

        void AerialHit::onDown(const Event & e)
        {
            State::onDown(e);
        }

        void AerialHit::onLeft(const Event & e)
        {
            State::onLeft(e);
        }

        void AerialHit::onRight(const Event & e)
        {
            State::onRight(e);
        }

        void AerialHit::onNextFrame()
        {
            State::onNextFrame();
        }
        
        void AerialHit::onAnimationEnd()
        {
            State::onAnimationEnd();
            Movement newMvt(_mvt);
            newMvt.setAction(Movement::Falling);
            switchState(newMvt);
        }
    }
}
