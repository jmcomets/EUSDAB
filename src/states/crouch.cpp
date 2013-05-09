#include <states/crouch.h>

namespace EUSDAB
{
    namespace States
    {
        Crouch::Crouch():
            State()
        {
        }

        Crouch::~Crouch()
        {
        }

        void Crouch::onUp(const Event & e)
        {
            State::onUp(e);
        }

        void Crouch::onDown(const Event & e)
        {
            State::onDown(e);
            if (_mvt == Movement::Left)
            {
                if ((e.edge == Event::FallingEdge)||(e.edge == Event::ContinuousEdge))
                {
                    switchState(Movement::Idle | Movement::Left);
                }
            }
            else if (_mvt == Movement::Right)
            {
                if (e.edge == Event::FallingEdge)
                {
                    switchState(Movement::Idle | Movement::Right);
                }
            }
        }

        void Crouch::onLeft(const Event & e)
        {
            State::onLeft(e);
            if ((e.edge == Event::RisingEdge)||(e.edge == Event::ContinuousEdge))
            {
                switchState(Movement::Crouch | Movement::Left);
            }
        }

        void Crouch::onRight(const Event & e)
        {
            State::onRight(e);
            if (e.edge == Event::RisingEdge)
            {
                switchState(Movement::Crouch | Movement::Right);
            }
        }

        void Crouch::onNextFrame()
        {
            State::onNextFrame();
        }
    }
}
