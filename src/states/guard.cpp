#include <states/guard.h>
#include <constants.h>

namespace EUSDAB
{
    namespace States
    {
        Guard::Guard(Movement const & m):
            State(m)
        {
        }

        Guard::~Guard()
        {
        }

        void Guard::onDown(const Event & e)
        {
            State::onDown(e);
            if (e.edge == Event::RisingEdge)
            {
                switchState(Movement::Dodge | Movement::Down | _mvt.direction());
            }
        }

        void Guard::onLeft(const Event & e)
        {
            State::onLeft(e);
            if (e.edge == Event::RisingEdge)
            {
                switchState(Movement::Dodge | Movement::Left);
            }
        }

        void Guard::onRight(const Event & e)
        {
            State::onRight(e);
            if (e.edge == Event::RisingEdge)
            {
                switchState(Movement::Dodge | Movement::Right);
            }
        }

        void Guard::onTrigger(const Event & e)
        {
            State::onTrigger(e);
            if (e.edge == Event::FallingEdge)
            {
                switchState(Movement::Idle | _mvt.direction());
            }
        }

        void Guard::onAnimationEnd()
        {
            State::onAnimationEnd();
            Movement newMvt(_mvt);
            newMvt.setAction(Movement::Shield);
            switchState(newMvt);
        }
    }
}
