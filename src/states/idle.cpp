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
            if (e.edge == Event::RisingEdge)
            {
                if (_mvt.flag() & Movement::Left)
                {
                    switchState(Movement::Jump | Movement::Left);
                }
                else if (_mvt.flag() & Movement::Right)
                {
                    switchState(Movement::Jump | Movement::Right);
                }
                else
                {
                    switchState(Movement::Jump | Movement::Left);
                }
            }

        }

        void Idle::onDown(const Event & e)
        {
            State::onDown(e);
            if ((e.edge == Event::RisingEdge)||(e.edge == Event::ContinuousEdge))
            {
                if (_mvt.flag() & Movement::Left)
                {
                    //switchState(Movement::Crouch | Movement::Left);
                }
                else if (_mvt.flag() & Movement::Right)
                {
                    //switchState(Movement::Crouch | Movement::Right);
                }
            }
        }

        void Idle::onLeft(const Event & e)
        {
            State::onLeft(e);
            if ((e.edge == Event::RisingEdge))
            {
                if(e.ratio > 0.75)
                {
                    switchState(Movement::Run | Movement::Left);
                }
                else
                {
                    switchState(Movement::Walk | Movement::Left);
                }
            }
        }

        void Idle::onRight(const Event & e)
        {
            State::onRight(e);
            
            if ((e.edge == Event::RisingEdge))
            {
                if(e.ratio > 0.75)
                {
                    switchState(Movement::Run | Movement::Right);
                }
                else
                {
                    switchState(Movement::Walk | Movement::Right);
                }
            }
        }

        void Idle::onNextFrame()
        {
            State::onNextFrame();
        }
    }
}
