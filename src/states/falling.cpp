#include <states/falling.h>

namespace EUSDAB
{
    namespace States
    {
        Falling::Falling():
            State()
        {
        }

        Falling::~Falling()
        {
        }

        void Falling::onUp(const Event & e)
        {
            State::onUp(e);
        }

        void Falling::onDown(const Event & e)
        {
            State::onDown(e);
        }

        void Falling::onLeft(const Event & e)
        {
            State::onLeft(e);
            if ((e.edge == Event::RisingEdge)||(e.edge == Event::ContinuousEdge))
            {
                switchState(Movement::Falling | Movement::Left);
            }
            else
            {
                //switchState(Movement::FallingIdle | Movement::Left);
            }
        }

        void Falling::onRight(const Event & e)
        {
            State::onRight(e);
            if ((e.edge == Event::RisingEdge)||(e.edge == Event::ContinuousEdge))
            {
                switchState(Movement::Falling | Movement::Right);
            }
            else
            {
                //switchState(Movement::FallingIdle | Movement::Right);
            }
        }

        void Falling::onNextFrame()
        {
            State::onNextFrame();
        }
    }
}
