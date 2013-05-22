#include <states/jump.h>
#include <iostream>
#include <constants.h>

namespace EUSDAB
{
    namespace States
    {
        Jump::Jump(Movement const & m):
            State(m), _velocity(0, 4)
        {
        }

        Jump::~Jump()
        {
        }

        void Jump::onUp(const Event & e)
        {
            State::onUp(e);
            if (e.edge == Event::RisingEdge)
            {
                if(e.ratio > Constants::OnRunRatio)
                {
                    std::cout << "Jump : onUp" << std::endl;
                    if (entity()->canJump() && entity()->jumpPossible())
                    {
                        switchState(Movement::Jump | _mvt.direction());
                    }
                }
            }
        }

        void Jump::onDown(const Event & e)
        {
            State::onDown(e);
            if (e.edge == Event::RisingEdge)
            {
                if(abs(e.ratio) > Constants::OnRunRatio)
                {
                    std::cout << "Jump : onDown" << std::endl;
                    _entity->physics().velocity().y = 0.1;
                    switchState(Movement::Falling | _mvt.direction());
                    entity()->setJumpPossible(true);
                }
            }
        }

        void Jump::onGround(const Event & e)
        {
            State::onGround(e);
            if(_entity->physics().velocity().y > 0)
            {
                std::cout << "Jump : OnGround" << std::endl;
                if (e.edge == Event::RisingEdge)
                {
                    switchState(Movement::Idle | _mvt.direction());
                    //entity()->setJumpPossible(true);
                    entity()->setNbrJump(entity()->nbrJumpMax());
                }
            }
        }

        void Jump::onLeft(const Event & e)
        {
            State::onLeft(e);

            if (e.edge == Event::RisingEdge)
            {
                std::cout << "Jump : onLeft" << std::endl;
                _entity->physics().velocity().x = -3;
                onChangeSide(Movement::Jump | Movement::Left);
                setNextStateAnimationFrameToCurrentFrame();
            }
            else if(e.edge == Event::FallingEdge)
            {
                _entity->physics().velocity().x = 0;
                //switchState(Movement::Jump | Movement::Idle | Movement::Left);
            }
        }

        void Jump::onRight(const Event & e)
        {
            State::onRight(e);
            if (e.edge == Event::RisingEdge)
            {
                std::cout << "Jump : onRight" << std::endl;
                _entity->physics().velocity().x = 3;
                onChangeSide(Movement::Jump | Movement::Right);
                setNextStateAnimationFrameToCurrentFrame();
            }
            else if(e.edge == Event::FallingEdge)
            {
                _entity->physics().velocity().x = 0;
                //switchState(Movement::Jump | Movement::Idle | Movement::Right);
            }
        }

        void Jump::onA(const Event & e)
        {
            State::onA(e);
            std::cout << "Jump : A" << std::endl;
            if ((e.edge == Event::RisingEdge))
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

        void Jump::onB(const Event & e)
        {
            std::cout << "Jump : B" << std::endl;
            State::onB(e);

            if (e.edge == Event::RisingEdge)
            {
                if(_entity->_verticalState == Entity::VerticalState::Middle)
                {
                    switchState(Movement::Special | Movement::Idle | _mvt.direction());
                }
                else if(_entity->_verticalState == Entity::VerticalState::Up)
                {
                    switchState(Movement::Special | Movement::Up | _mvt.direction());
                }
                else if(_entity->_verticalState == Entity::VerticalState::Down)
                {
                    switchState(Movement::Special | Movement::Down | _mvt.direction());
                }
            }
        }



        void Jump::onNextFrame()
        {
            State::onNextFrame();

            //std::cout << _entity->physics() << std::endl;
            //std::cout << "_velocity : " << _velocity.y << " | transform : " << _entity->physics().velocity().y << std::endl;
            //FIXME
            // Shorten code !
            using Physics::Unit;

            if (_entity->physics().velocity().y > 0)
            {
                std::cout << "Jump : OnNext < 0" << std::endl;
                switchState(Movement::Falling | _mvt.direction());
                //entity()->setJumpPossible(true);
            }

        else if (!_entity->jumpPossible() && std::abs(_entity->physics().velocity().y) < std::abs(_velocity.y / 2))
            {
                std::cout << "Jump : OnNext y < /2" << std::endl;
                _entity->setJumpPossible(true);
            }
        }



        void Jump::onEnter()
        {
            // TODO add vertical impulse

            std::cout << "Jump : onEnter " << std::endl;
            _velocity.y = 12;
            _animation->setPaused(false);
            _entity->setJumpPossible(false);
            _entity->setNbrJump(entity()->nbrJump()-1);

            if(_mvt.flag() & Movement::Left)
            {
                _entity->physics().velocity().y = _velocity.y;
                //_entity->physics().velocity().x *= static_cast<Physics::Unit>(-1);
                _entity->physics().velocity().y *= static_cast<Physics::Unit>(-1);
            }
            if(_mvt.flag() & Movement::Right)
            {
                _entity->physics().velocity().y = _velocity.y;
                _entity->physics().velocity().y *= static_cast<Physics::Unit>(-1);
            }
            std::cout << "Velocity : " << _velocity.x << " | transform : " << _entity->physics().velocity().y << std::endl;
        }

        void Jump::onLeave()
        {
            State::onLeave();
            std::cout << "Jump : onLeave" << std::endl;
            _entity->setJumpPossible(true);
        }

        void Jump::onChangeSide(const Movement & mvt)
        {
            State * s = _entity->state();

            if(_mvt.flag() & Movement::Left)
            {
                //s->transformation().velocity() = _velocity;
                //s->transformation().velocity().x *= static_cast<Physics::Unit>(-1);
                //s->transformation().velocity().y=_entity->physics().velocity().y;
                //_entity->physics().velocity().y *= static_cast<Physics::Unit>(-1);
            }
            if(_mvt.flag() & Movement::Right)
            {
                //s->transformation().velocity() = _velocity;
                //s->transformation().velocity().y=_entity->physics().velocity().y;
                //_entity->physics().velocity().y *= static_cast<Physics::Unit>(-1);
            }
        }


        void Jump::onAnimationEnd()
        {
            _animation->setPaused();
            _animation->explicitAdvance(-1);
        }

        void Jump::setNextStateAnimationFrameToCurrentFrame() const
        {
            // Continue animation from current frame in next state
            State * s = _entity->state();
            if (s == nullptr) { return; }

            Animation * a = s->animation();
            if (a == nullptr) { return; }
            a->setCurrentFrame(_animation->currentFrame());
        }

        void Jump::setVelocity(const  Physics::Vector2 & value)
        {
            _velocity=value;
        }

        void Jump::onMiddleOfJump()
        {

        }

        void Jump::onJumpEnd()
        {

        }
    }
}
