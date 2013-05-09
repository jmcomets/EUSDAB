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
        }

        void Idle::onLeft(const Event & e)
        {
            State::onLeft(e);
            if (_mov == Movement::Left)
            {
                if ((e.edge == Event::RisingEdge)||(e.edge == Event::ContinuousEdge))
                {
                    switchState(Movement::walk | Movement::Left);
                }
                else
                {
                    switchState(Movement::Idle | Movement::Left);
                }
            }
            else if (_mov == Movement::Right)
            {
                if ((e.edge == Event::RisingEdge)||(e.edge == Event::ContinuousEdge))
                {
                    switchState(Movement::Walk | Movement::Right);
                }
                else
                {
                    switchState(Movement::Idle | Movement::Right);
                }
            }
            
            
        }

        void Idle::onRight(const Event & e)
        {
            State::onRight(e);
            if (_mov == Movement::Left)
            {
                if ((e.edge == Event::RisingEdge)||(e.edge == Event::ContinuousEdge))
                {
                    switchState(Movement::walk | Movement::Left);
                }
                else
                {
                    switchState(Movement::Idle | Movement::Left);
                }
            }
            else if (_mov == Movement::Right)
            {
                if ((e.edge == Event::RisingEdge)||(e.edge == Event::ContinuousEdge))
                {
                    switchState(Movement::Walk | Movement::Right);
                }
                else
                {
                    switchState(Movement::Idle | Movement::Right);
                }
            }
        }

        void Idle::onNextFrame()
        {
            State::onNextFrame();
        }
    }
}
