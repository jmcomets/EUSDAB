#include <states/attack.h>
#include <cmath>
#include <iostream>

namespace EUSDAB
{
    namespace States
    {
        Attack::Attack(Movement const & m):
            State(m)
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
            std::cout << "mvt.flag() before : " << _mvt.flag() << std::endl;
            // _mvt.setFlag(_mvt.flag() & ~Movement::Up & ~Movement::Down);
            std::cout << "mvt.flag() after : " << _mvt.flag() << std::endl;
            Movement newMvt(_mvt);
            newMvt.setAction(Movement::Idle);
            switchState(newMvt & ~Movement::Up & ~Movement::Down);
        }

        void Attack::onEnter()
        {
            State::onEnter();
        }

        void Attack::onLeave()
        {
            State::onLeave();
            _attack->reset();
        }

        void Attack::setSlidingRatio(Physics::Unit value)
        {
            _sliding_ratio=value;
        }
    }
}
