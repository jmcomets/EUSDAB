#include <states/run.h>
#include <iostream>

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

        void Run::onDown(const Event & e)
        {
            State::onDown(e);
        }

        void Run::onLeft(const Event & e)
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
                    switchState(Movement::Run | Movement::Left);
                }
            }
            else if(e.edge == Event::FallingEdge)
            {
                switchState(Movement::Idle | Movement::Left);
            }
        }

        void Run::onRight(const Event & e)
        {
            State::onRight(e);
           
            if (e.edge == Event::RisingEdge)
            {
                if(_mvt.flag() & Movement::Left)
                {
                    switchState(Movement::Walk | Movement::Right);
                    std::cout << "<Run::onRight> : Movement::Left" << std::endl;
                }
                else if(_mvt.flag() & Movement::Right)
                {
                    switchState(Movement::Run| Movement::Right);
                    std::cout << "<Run::onRight> : Movement::Right" << std::endl;
                }
            }
            else if(e.edge == Event::FallingEdge)
            {
                switchState(Movement::Idle | Movement::Right);
            }
        }

        void Run::onNextFrame()
        {
            Listener::onNextFrame();
            bool animationEnd=false;
            if (_animation != nullptr)
            {
                animationEnd=_animation->advance();
            }
            if (animationEnd)
            {
                 _animation->resetAnimation(); 
            }  
        }
    }
}
