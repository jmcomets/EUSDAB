#include <states/run.h>

namespace EUSDAB
{
    namespace States
    {
        Run::Run():
            State()
        {
        }

        Run::~Run()
        {
        }

        void Run::onUp(const Event & e)
        {
            State::onUp(e);
        }

        void Run::onDown(const Event & e)
        {
            State::onDown(e);
        }

        void Run::onLeft(const Event & e)
        {
            State::onLeft(e);
            if ((e.edge == Event::RisingEdge)||(e.edge == Event::ContinuousEdge))
            {
                switchState(Movement::Run | Movement::Left);
            }
            else
            {
                switchState(Movement::Idle | Movement::Left);
            }
        }

        void Run::onRight(const Event & e)
        {
            State::onRight(e);
           
            if ((e.edge == Event::RisingEdge)||(e.edge == Event::ContinuousEdge))
            {
                switchState(Movement::Run | Movement::Right);
            }
            else
            {
                switchState(Movement::Idle | Movement::Right);
            }
        }

        void Run::onNextFrame()
        {
            State::onNextFrame();
        }
    }
}
