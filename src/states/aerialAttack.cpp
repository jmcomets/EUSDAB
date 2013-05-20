#include <states/aerialAttack.h>
#include <cmath>
#include <iostream>

namespace EUSDAB
{
    namespace States
    {
        AerialAttack::AerialAttack():
            State()
        {
        }

        AerialAttack::~AerialAttack()
        {
        }

        void AerialAttack::onUp(const Event & e)
        {
            State::onUp(e);
        }

        void AerialAttack::onDown(const Event & e)
        {
            State::onDown(e);
        }

        void AerialAttack::onLeft(const Event & e)
        {
            State::onLeft(e);
        }

        void AerialAttack::onRight(const Event & e)
        {
            State::onRight(e); 
        }

        void AerialAttack::onNextFrame()
        {
            State::onNextFrame();

           /* // Shorten code !
            using Physics::Unit;

            // Sliding config
            constexpr Unit sliding_min = static_cast<Unit>(0.01);

            // Sliding code
            _transform.velocity().x /= _sliding_ratio;
            if (std::abs(_transform.velocity().x) < sliding_min)
            {
                _transform.velocity().x = static_cast<Unit>(0);
            }*/
        }

        void AerialAttack::onAnimationEnd()
        {
            State::onAnimationEnd();
            Movement newMvt(_mvt);
            newMvt.setAction(Movement::Falling);
            switchState(newMvt);
        }
        
        void AerialAttack::onEnter()
        {
            State::onEnter();
        }
        
        void AerialAttack::onLeave()
        {
            State::onLeave();
        }
        
       /* void AerialAttack::setSlidingRatio(Physics::Unit value)
        {
            _sliding_ratio=value;
        }*/
    }
}
