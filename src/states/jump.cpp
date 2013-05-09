#include <states/jump.h>
#include <iostream>

namespace EUSDAB
{
    namespace States
    {
        Jump::Jump():
            State()
        {
        }

        Jump::~Jump()
        {
        }

        void Jump::onUp(const Event & e)
        {
            State::onUp(e);
        }

        void Jump::onDown(const Event & e)
        {
            State::onDown(e);
            if (e.edge == Event::RisingEdge)
            {
                if (_mvt.flag() & Movement::Left)
                {
                    switchState(Movement::Falling | Movement::Left);
                }
                else if (_mvt.flag() & Movement::Right)
                {
                    switchState(Movement::Falling | Movement::Right);
                }
            }
        }

        void Jump::onLeft(const Event & e)
        {
            State::onLeft(e);
            if ((e.edge == Event::RisingEdge)||(e.edge == Event::ContinuousEdge))
            {
                switchState(Movement::Jump | Movement::Left);
            }
            else
            {
                //switchState(Movement::JumpIdle | Movement::Left);
            }
        }

        void Jump::onRight(const Event & e)
        {
            State::onRight(e);
            if ((e.edge == Event::RisingEdge)||(e.edge == Event::ContinuousEdge))
            {
                switchState(Movement::Jump | Movement::Right);
            }
            else
            {
                //switchState(Movement::JumpIdle | Movement::Right);
            }
        }

        void Jump::onNextFrame()
        {
            State::onNextFrame();
        }
    }
}
