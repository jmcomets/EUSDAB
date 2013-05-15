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

            static auto trajectoryY = [] (std::time_t t) {
                Physics::Unit t0 = static_cast<Physics::Unit>(t);
                static const Physics::Unit height = 10.0;
                static const Physics::Unit time_max = 10.0;

                if(t0 > time_max)
                    return Physics::Unit(0);
                return -t0 * height / time_max;
            };

            _transform.velocity().setX(
                    _transform.velocity().x() / 1.04);
            if(std::abs(_transform.velocity().x()) < 0.01)
            {
                _transform.velocity().setX(0.0);
            }

            if((_mvt.flag() & Movement::Left
                    || _mvt.flag() & Movement::Right)
                    && !(_mvt.flag() & Movement::Idle))
                _transform.velocity().setY(trajectoryY(_time));
        }

        void Special::onAnimationEnd()
        {
            State::onAnimationEnd();
            Movement newMvt(_mvt);
            newMvt.setAction(Movement::Idle);
            switchState(newMvt);
        }
        
        void Special::onEnter()
        {
            State::onEnter();
        }
        
        void Special::onLeave()
        {
            State::onLeave();
        }
        
      
    }
}
