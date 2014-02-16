
#include <states/run.h>
#include <iostream>

namespace EUSDAB
{
    namespace States
    {
        Run::Run(Movement const & m):
            Motion(m)
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
                if (entity()->canJump()&&entity()->jumpPossible())
                {
                    //switchState(Movement::Jump | _mvt.direction());
                    switchStateWithVelocity(Movement::Jump | _mvt.direction());
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
                if (_mvt.flag() & Movement::Right)
                {
                    switchState(Movement::Walk | Movement::Left);
                }
                else if (_mvt.flag() & Movement::Left)
                {
                    switchState(Movement::Run | Movement::Left);
                }
            }
            else if (e.edge == Event::FallingEdge)
            {
                switchState(Movement::Idle | Movement::Left);
            }
        }

        void Run::onRight(const Event & e)
        {
            State::onRight(e);

            if (e.edge == Event::RisingEdge)
            {
                if (_mvt.flag() & Movement::Left)
                {
                    switchState(Movement::Walk | Movement::Right);
                }
                else if (_mvt.flag() & Movement::Right)
                {
                    switchState(Movement::Run| Movement::Right);
                }
            }
            else if (e.edge == Event::FallingEdge)
            {
                switchState(Movement::Idle | Movement::Right);
            }
        }

        void Run::onEnter()
        {
            State::onEnter();

            if (_mvt.flag() & Movement::Left)
            {
                _transform.velocity() = _velocity;
                // _transform.velocity().x *= static_cast<Physics::Unit>(-1);
            }
            else if (_mvt.flag() & Movement::Right)
            {
                _transform.velocity() = _velocity;
            }
        }

        void Run::onLeave()
        {
            State::onLeave();
        }
    }
}
