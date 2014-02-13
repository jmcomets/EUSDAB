#include <states/falling.h>
#include <constants.h>

namespace EUSDAB
{
    namespace States
    {
        Falling::Falling(Movement const & m):
            State(m)
        {
        }

        Falling::~Falling()
        {
        }

        void Falling::onUp(const Event & e)
        {
            State::onUp(e);
            if (e.edge == Event::RisingEdge)
            {
                if (entity()->canJump() && entity()->jumpPossible())
                {
                    switchState(Movement::Jump | _mvt.direction());
                }
            }
        }

        void Falling::onLeft(const Event & e)
        {
            State::onLeft(e);
            if (e.edge == Event::RisingEdge)
            {
                _transform.velocity().x = _velocity.x;
                switchState(Movement::Falling | Movement::Left);
            }
            else if (e.edge == Event::FallingEdge)
            {
                _transform.velocity().x = 0;
            }
        }

        void Falling::onRight(const Event & e)
        {
            State::onRight(e);
            if (e.edge == Event::RisingEdge)
            {
                _transform.velocity().x = _velocity.x;
                switchState(Movement::Falling | Movement::Right);
            }
            else if (e.edge == Event::FallingEdge)
            {
                _transform.velocity().x = 0;
            }
        }

        void Falling::onA(const Event & e)
        {
            State::onA(e);
            if (e.edge == Event::RisingEdge)
            {
                if (_mvt.flag() & Movement::Left)
                {
                    switchState(Movement::AerialAttack | _mvt.direction());
                }
                else if (_mvt.flag() & Movement::Right)
                {
                    switchState(Movement::AerialAttack | _mvt.direction());
                }
                else
                {
                    //switchState(Movement::Attack | Movement::Left);
                }
            }
        }

        void Falling::onB(const Event & e)
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
                    if (_entity->nbrJump() > 0)
                    {
                        switchState(Movement::Special | Movement::Up | _mvt.direction());
                    }
                }
                else if (_entity->_verticalState == Entity::VerticalState::Down)
                {
                    switchState(Movement::Special | Movement::Down | _mvt.direction());
                }
            }

        }

        void Falling::onGround(const Event & e)
        {
            State::onGround(e);
            if (e.edge == Event::RisingEdge)
            {
                switchState(Movement::Idle | _mvt.direction());
                _entity->setNbrJump(_entity->nbrJumpMax());
            }
        }
        
        void Falling::setNextStateAnimationFrameToCurrentFrame() const
        {
            // Continue animation from current frame in next state
            State * s = _entity->state();
            if (s == nullptr) { return; }

            Animation * a = s->animation();
            if (a == nullptr) { return; }
            a->setCurrentFrame(_animation->currentFrame());
        }
        
        void Falling::setVelocity(const  Physics::Vector2 & value)
        {
            _velocity = value;      
        }
        
    }
}
