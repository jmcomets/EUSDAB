#include <states/attack.h>
#include <cmath>
#include <iostream>

namespace EUSDAB
{
    namespace States
    {
        Attack::Attack():
            State()
        {
        }

        Attack::~Attack()
        {
        }

        void Attack::onUp(const Event & e)
        {
            State::onUp(e);
        }

        void Attack::onDown(const Event & e)
        {
            State::onDown(e);
        }

        void Attack::onLeft(const Event & e)
        {
            State::onLeft(e);
        }

        void Attack::onRight(const Event & e)
        {
            State::onRight(e); 
        }

        void Attack::onNextFrame()
        {
            State::onNextFrame();

            // Shorten code !
            using Physics::Unit;

            // Sliding config
            constexpr Unit sliding_min = static_cast<Unit>(0.01);

            // Sliding code
            _transform.velocity().x /= _sliding_ratio;
            if (std::abs(_transform.velocity().x) < sliding_min)
            {
                _transform.velocity().x = static_cast<Unit>(0);
            }
        }

        void Attack::onAnimationEnd()
        {
            State::onAnimationEnd();
            Movement newMvt(_mvt);
            newMvt.setAction(Movement::Idle);
            switchState(newMvt);
        }
        
        void Attack::onEnter()
        {
            State::onEnter();
        }
        
        void Attack::onLeave()
        {
            State::onLeave();
        }
        
        void Attack::setSlidingRatio(Physics::Unit value)
        {
            _sliding_ratio=value;
        }
    }
}
