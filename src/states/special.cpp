#include <states/special.h>
#include <cmath>
#include <iostream>

namespace EUSDAB
{
    namespace States
    {
        Special::Special():
            State()
        {
        }

        Special::~Special()
        {
        }

        void Special::onUp(const Event & e)
        {
            State::onUp(e);
        }

        void Special::onDown(const Event & e)
        {
            State::onDown(e);
        }

        void Special::onLeft(const Event & e)
        {
            State::onLeft(e);
        }

        void Special::onRight(const Event & e)
        {
            State::onRight(e);
        }

        void Special::onNextFrame()
        {
            State::onNextFrame();

            // Shorten code !
            using Physics::Unit;

            static auto trajectoryY = [] (std::time_t t)
            {
                // Be explicit
                const Unit t0 = static_cast<Unit>(t);
                constexpr Unit height = static_cast<Unit>(10.0);
                constexpr Unit time_max = static_cast<Unit>(10.0);

                if (t0 > time_max)
                {
                    return static_cast<Unit>(0);
                }
                return -t0 * height / time_max;
            };

            // Sliding config
            constexpr Unit sliding_ratio = static_cast<Unit>(1.005);
            constexpr Unit sliding_min = static_cast<Unit>(0.01);

            // Sliding code
            _transform.velocity().x /= sliding_ratio;
            if (std::abs(_transform.velocity().x) < sliding_min)
            {
                _transform.velocity().x = static_cast<Unit>(0);
            }

            if ((_mvt.flag() & Movement::Left
                    || _mvt.flag() & Movement::Right)
                    && !(_mvt.flag() & Movement::Idle))
            {
                _transform.velocity().y = trajectoryY(_time);
            }
        }

        void Special::onAnimationEnd()
        {
            State::onAnimationEnd();
            Movement newMvt(_mvt);
            newMvt.setAction(Movement::Idle);
            switchState(newMvt);
        }

        void Special::onGround(const Event & e)
        {
            State::onGround(e);
        }
        
        void Special::onEnter()
        {
            State::onEnter();
        }
        
        void Special::onLeave()
        {
            State::onLeave();
            _attack->reset();
        }
        
      
    }
}
