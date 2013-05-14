#include <states/attack.h>
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

            // FIXME
            _transform.velocity() /= 1.04;
            if(_transform.velocity().norm() < 0.01)
            {
                _transform.velocity() = Physics::Vector2();
            }
            std::cout << _transform.velocity().x() << std::endl;
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
    }
}
