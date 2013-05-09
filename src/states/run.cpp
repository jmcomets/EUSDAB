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
            if (_mvt == Movement::Left)
            {
                if (e.edge == Event::RisingEdge)
                {
                    switchState(Movement::Run | Movement::Left);
                }
                else
                {
                    switchState(Movement::Idle | Movement::Left);
                }
            }
            else if (_mvt == Movement::Right)
            {
                if (e.edge == Event::RisingEdge)
                {
                    switchState(Movement::Walk | Movement::Right);
                }
                else
                {
                    switchState(Movement::Idle | Movement::Right);
                }
            }
        }

        void Run::onRight(const Event & e)
        {
            State::onRight(e);
            if (_mvt == Movement::Left)
            {
                if (e.edge == Event::RisingEdge)
                {
                    switchState(Movement::Walk | Movement::Left);
                }
                else
                {
                    switchState(Movement::Idle | Movement::Left);
                }
            }
            else if (_mvt == Movement::Right)
            {
                if (e.edge == Event::RisingEdge)
                {
                    switchState(Movement::Run | Movement::Right);
                }
                else
                {
                    switchState(Movement::Idle | Movement::Right);
                }
            }
        }

        void Run::onNextFrame()
        {
            State::onNextFrame();
        }
    }
}
