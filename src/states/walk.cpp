#include <states/walk.h>
#include <constants.h>
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
            if (e.edge == Event::RisingEdge)
            {
                if (e.edge == Event::RisingEdge)
                {
                    if (entity()->canJump()&&entity()->jumpPossible())
                    {
                        switchState(Movement::Jump | _mvt.direction());
                    }
                }
            }
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
                else if((_mvt.flag() & Movement::Left) && e.ratio > Constants::OnRunRatio)
                {
                    switchState(Movement::Run | Movement::Left);
                }
            }
            else if(e.edge == Event::FallingEdge)
            {
                std::cout << "<Walk::onLeft> : Movement::Left | FallingEdge" << std::endl;
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
                else if((_mvt.flag() & Movement::Right) && e.ratio > Constants::OnRunRatio)
                {
                    switchState(Movement::Run | Movement::Right);
                    std::cout << "<Walk::onRight> : Movement::Right" << std::endl;
                }
            }
            else if(e.edge == Event::FallingEdge)
            {
                std::cout << "<Walk::onRight> : Movement::Right | FallingEdge" << std::endl;
                switchState(Movement::Idle | Movement::Right);
            }
        }
        
        void Walk::onA(const Event & e)
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
        
        void Walk::onB(const Event & e)
        {
            State::onB(e);
            if (e.edge == Event::RisingEdge)
            {
                if (_mvt.flag() & Movement::Left)
                {
                    switchState(Movement::Special | Movement::Left);
                }
                else if (_mvt.flag() & Movement::Right)
                {
                    switchState(Movement::Special | Movement::Right);
                }
                else
                {
                    //switchState(Movement::Attack | Movement::Left);
                }
            }
        }

        void Walk::onNextFrame()
        {
            State::onNextFrame();
        }

        void Walk::onEnter()
        {
            State::onEnter();

            if(_mvt.flag() & Movement::Left)
                _transform.velocity() = Physics::Vector2(-1.0 , 0);
            if(_mvt.flag() & Movement::Right)
                _transform.velocity() = Physics::Vector2(1.0 , 0);
        }
    }
}
