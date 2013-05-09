#include <states/idle.h>

namespace EUSDAB
{
    namespace States
    {
        Idle::Idle():
            State()
        {
        }

        Idle::~Idle()
        {
        }

        void Idle::onUp(const Event & e)
        {
            State::onUp(e);
        }

        void Idle::onDown(const Event & e)
        {
            State::onDown(e);
            if ((e.edge == Event::RisingEdge)||(e.edge == Event::ContinuousEdge))
            {
                if (_mov == Movement::Left)
                {
                    switchState(Movement::Crouch | Movement::Left);
                }
                else if (_mov == Movement::Right)
                {
                    switchState(Movement::Crouch | Movement::Right);
                }
            }
        }

        void Idle::onLeft(const Event & e)
        {
            State::onLeft(e);
            if ((e.edge == Event::RisingEdge)||(e.edge == Event::ContinuousEdge))
            {
                switchState(Movement::Walk | Movement::Left);
            }
            else
            {
                switchState(Movement::Idle | Movement::Left);
            }
        
            
        }

        void Idle::onRight(const Event & e)
        {
            State::onRight(e);
            
            if ((e.edge == Event::RisingEdge)||(e.edge == Event::ContinuousEdge))
            {
                switchState(Movement::Walk | Movement::Right);
            }
            else
            {
                switchState(Movement::Idle | Movement::Right);
            }
        }

        void Idle::onNextFrame()
        {
            State::onNextFrame();
        }
    }
}
