#include <states/walk.h>
#include <iostream>

namespace EUSDAB
{
    namespace States
    {
        Walk::Walk():
            State()
        {
        }

        Walk::~Walk()
        {
        }

        void Walk::onUp(const Event & e)
        {
            State::onUp(e);
        }

        void Walk::onDown(const Event & e)
        {
            State::onDown(e);
        }

        void Walk::onLeft(const Event & e)
        {
            State::onLeft(e);
            if (e.edge == Event::RisingEdge)
            {
                if(_mvt.flag() & Movement::Right)
                {
                    switchState(Movement::Walk | Movement::Left);
                }
                else if(_mvt.flag() & Movement::Left)
                {
                    switchState(Movement::Run| Movement::Left);
                }
            }
            else if(e.edge == Event::FallingEdge)
            {
                switchState(Movement::Idle | Movement::Left);
            }
        }

        void Walk::onRight(const Event & e)
        {
            State::onRight(e);
           
            if (e.edge == Event::RisingEdge)
            {
                if(_mvt.flag() & Movement::Left)
                {
                    switchState(Movement::Walk | Movement::Right);
                    std::cout << "<Walk::onRight> : Movement::Left" << std::endl;
                }
                else if(_mvt.flag() & Movement::Right)
                {
                    switchState(Movement::Run| Movement::Right);
                    std::cout << "<Walk::onRight> : Movement::Right" << std::endl;
                }
            }
            else if(e.edge == Event::FallingEdge)
            {
                switchState(Movement::Idle | Movement::Right);
            }
        }

        void Walk::onNextFrame()
        {
            State::onNextFrame();
        }
    }
}
