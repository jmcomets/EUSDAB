#include <states/idle.h>
#include <constants.h>

namespace EUSDAB
{
    namespace States
    {
        Idle::Idle(Movement const & m):
            State(m)
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
                if (e.ratio > Constants::OnRunRatio)
                {
                    if (entity()->canJump() && entity()->jumpPossible())
                    {
                        switchState(Movement::Jump | _mvt.direction());
                    }
                }
            }
        }

        void Idle::onTrigger(const Event & e)
        {
            State::onTrigger(e);
            if (e.edge == Event::RisingEdge)
            {
				switchState(Movement::Guard | _mvt.direction());
            }

        }

        void Idle::onDown(const Event & e)
        {
            State::onDown(e);
            if (e.edge == Event::RisingEdge)
            {
                if (e.ratio > Constants::OnRunRatio)
                {
                    switchState(Movement::Crouch | _mvt.direction());
                }
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
            if (e.edge == Event::RisingEdge)
            {
                if (_entity->_verticalState == Entity::VerticalState::Middle)
                {
                    switchState(Movement::Attack | _mvt.direction());
                }
                else if (_entity->_verticalState == Entity::VerticalState::Up)
                {
                    switchState(Movement::Attack | Movement::Up | _mvt.direction());
                }
                else if (_entity->_verticalState == Entity::VerticalState::Down)
                {
                    switchState(Movement::Attack | Movement::Down | _mvt.direction());
                }
            }
        }

        void Idle::onB(const Event & e)
        {
            State::onB(e);
            if (e.edge == Event::RisingEdge)
            {
                if (_entity->_verticalState == Entity::VerticalState::Middle)
                {
                    switchState(Movement::Special | Movement::Idle | _mvt.direction());
                }
                else if (_entity->_verticalState == Entity::VerticalState::Up)
                {
                    switchState(Movement::Special | Movement::Up | _mvt.direction());
                }
                else if (_entity->_verticalState == Entity::VerticalState::Down)
                {
                    switchState(Movement::Special | Movement::Down | _mvt.direction());
                }
            }
        }

        void Idle::onNextFrame()
        {
            State::onNextFrame();

            if (_entity->physics().velocity().y > 0)
            {
                switchState(Movement::Falling | _mvt.direction());
            }
        }

        void Idle::setSlidingRatio(const Physics::Unit & value)
        {
            _sliding_ratio = value;
        }
    }
}
