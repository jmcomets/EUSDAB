#include <states/walk.h>
#include <constants.h>
#include <iostream>

namespace EUSDAB
{
    namespace States
    {
        Walk::Walk(Movement const & m):
            Motion(m)
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
                    if (_entity->canJump() && _entity->jumpPossible())
                    {
                        switchState(Movement::Jump | _mvt.direction());
                    }
                }
            }
        }

        void Walk::onLeft(const Event & e)
        {
            State::onLeft(e);
            if (e.edge == Event::RisingEdge)
            {
                if (_mvt.flag() & Movement::Right)
                {
                    switchState(Movement::Walk | Movement::Left);
                }
                else if ((_mvt.flag() & Movement::Left) && e.ratio > Constants::OnRunRatio)
                {
                    switchState(Movement::Run | Movement::Left);
                }
            }
            else if (e.edge == Event::FallingEdge)
            {
                switchState(Movement::Idle | Movement::Left);
            }
        }

        void Walk::onRight(const Event & e)
        {
            State::onRight(e);
           
            if (e.edge == Event::RisingEdge)
            {
                if (_mvt.flag() & Movement::Left)
                {
                    switchState(Movement::Walk | Movement::Right);
                }
                else if ((_mvt.flag() & Movement::Right) && e.ratio > Constants::OnRunRatio)
                {
                    switchState(Movement::Run | Movement::Right);
                }
            }
            else if(e.edge == Event::FallingEdge)
            {
                std::cout << "<Walk::onRight> : Movement::Right | FallingEdge" << std::endl;
                switchState(Movement::Idle | Movement::Right);
            }
        }
        
        void Walk::onNextFrame()
        {
            State::onNextFrame();
            if (_entity->physics().velocity().y > 0)
            {
                switchStateWithVelocity(Movement::Falling | _mvt.direction());
            }
        }

        void Walk::onEnter()
        {
            State::onEnter();

            if (_mvt.flag() & Movement::Left)
            {
                _transform.velocity() = _velocity;
                _transform.velocity().x *= static_cast<Physics::Unit>(-1);
            }
            else if (_mvt.flag() & Movement::Right)
            {
                _transform.velocity() = _velocity;
            }
        }
    }
}
