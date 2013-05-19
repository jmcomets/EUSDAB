#include <states/idle.h>
#include <constants.h>

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
                if (entity()->canJump()&&entity()->jumpPossible())
                {
                    switchState(Movement::Jump | _mvt.direction());
                }
            }

        }

        void Idle::onDown(const Event & e)
        {
            State::onDown(e);
            if (e.edge == Event::RisingEdge || e.edge == Event::ContinuousEdge)
            {
                //switchState(Movement::Crouch | _mvt.direction());
            }
        }

        void Idle::onLeft(const Event & e)
        {
            State::onLeft(e);
            if (e.edge == Event::RisingEdge)
            {
                if (e.ratio > Constants::OnRunRatio)
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
            
            if (e.edge == Event::RisingEdge)
            {
                if (e.ratio > Constants::OnRunRatio)
                {
                    switchState(Movement::Run | Movement::Right);
                }
                else
                {
                    switchState(Movement::Walk | Movement::Right);
                }
            }
        }
        
        void Idle::onA(const Event & e)
        {
            State::onA(e);
            if ((e.edge == Event::RisingEdge))
            {
                if (_mvt.flag() & Movement::Left)
                {
                    switchState(Movement::Attack | Movement::Left);
                }
                else if (_mvt.flag() & Movement::Right)
                {
                    switchState(Movement::Attack | Movement::Right);
                }
                else
                {
                    //switchState(Movement::Attack | Movement::Left);
                }
            }
        }
        
        void Idle::onB(const Event & e)
        {
            State::onB(e);
            if (e.edge == Event::RisingEdge)
            {
                switchState(Movement::Special | Movement::Idle | _mvt.direction());
            }
        }

        void Idle::onNextFrame()
        {
            State::onNextFrame();
        }
    }
}
