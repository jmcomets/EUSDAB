
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
                if (e.edge == Event::RisingEdge)
                {
                    if (entity()->canJump()&&entity()->jumpPossible())
                    {
                        switchState(Movement::Jump | _mvt.direction());
                    }
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
        
        void Run::onA(const Event & e)
        {
            State::onA(e);
            if ((e.edge == Event::RisingEdge))
            {
                if (_mvt.flag() & Movement::Left)
                {
                    switchState(Movement::Attack | Movement::Left);
                    auto s = _entity->state();
                    if(s != nullptr)
                    {
                        s->transformation().velocity() = Physics::Vector2(-6.0 , 0);
                    }
                }
                else if (_mvt.flag() & Movement::Right)
                {
                    switchState(Movement::Attack | Movement::Right);
                    auto s = _entity->state();
                    if(s != nullptr)
                    {
                        s->transformation().velocity() = Physics::Vector2(6.0 , 0);
                    }
                }
                else
                {
                    //switchState(Movement::Attack | Movement::Left);
                }
            }
        }
        
        void Run::onB(const Event & e)
        {
            State::onB(e);
            if ((e.edge == Event::RisingEdge))
            {
                if (_mvt.flag() & Movement::Left)
                {
                    switchState(Movement::Special | Movement::Left);
                    auto s = _entity->state();
                    if(s != nullptr)
                    {
                        s->transformation().velocity() = Physics::Vector2(-10.0 , 0);
                    }
                }
                else if (_mvt.flag() & Movement::Right)
                {
                    switchState(Movement::Special | Movement::Right);
                    auto s = _entity->state();
                    if(s != nullptr)
                    {
                        s->transformation().velocity() = Physics::Vector2(10.0 , 0);
                    }
                }
                else
                {
                    //switchState(Movement::Attack | Movement::Left);
                }
            }
        }

        void Run::onNextFrame()
        {
            Listener::onNextFrame();
            if (_animation != nullptr)
            {
                _animation->advance();
            }
        }

        void Run::onEnter()
        {
            State::onEnter();

            if(_mvt.flag() & Movement::Left)
                _transform.velocity() = _velocity;
                _transform.velocity().x*=-1;
            if(_mvt.flag() & Movement::Right)
                _transform.velocity() = _velocity;
        }
        
        void Run::setVelocity(const  Physics::Vector2 & value)
        {
            _velocity=value;      
        }
    }
}
