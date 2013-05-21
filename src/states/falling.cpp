#include <states/falling.h>

namespace EUSDAB
{
    namespace States
    {
        Falling::Falling():
            State()
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

        void Falling::onDown(const Event & e)
        {
            State::onDown(e);
        }

        void Falling::onLeft(const Event & e)
        {
            State::onLeft(e);
            if (e.edge == Event::RisingEdge)
            {
                _entity->physics().velocity().x = -3;
                onChangeSide(Movement::Falling | Movement::Left);
            }
            else if(e.edge == Event::FallingEdge)
            {
                _entity->physics().velocity().x = 0;
                //switchState(Movement::Falling | Movement::Idle | Movement::Left);
            }
        }

        void Falling::onRight(const Event & e)
        {
            State::onRight(e);
            if (e.edge == Event::RisingEdge)
            {
                _entity->physics().velocity().x = 3;
                onChangeSide(Movement::Falling | Movement::Right);
            }
            else if(e.edge == Event::FallingEdge)
            {
                _entity->physics().velocity().x = 0;
                //switchState(Movement::FallingIdle | Movement::Right);
            }
        }

        void Falling::onA(const Event & e)
        {
            State::onA(e);
            std::cout << "Falling : A" << std::endl;
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

        void Falling::onB(const Event & e)
        {
            std::cout << "Falling : B" << std::endl;
            State::onB(e);
            if (e.edge == Event::RisingEdge)
            {
                if(std::abs(_entity->physics().velocity().x) > 0)
                {
                    switchState(Movement::Special | _mvt.direction());
                }
                else
                {
                    switchState(Movement::Special | Movement::Idle | _mvt.direction());
                }
            }
        }

        void Falling::onGround(const Event & e)
        {
            State::onGround(e);
            if (e.edge == Event::RisingEdge || e.edge == Event::ContinuousEdge)
            {
                switchState(Movement::Idle | _mvt.direction());
                entity()->setNbrJump(entity()->nbrJumpMax());
            }
        }



        void Falling::onNextFrame()
        {
            State::onNextFrame();
        }
        
        void Falling::onEnter()
        {
            // TODO add vertical impulse

            std::cout << "Falling : onEnter" << std::endl;
            _animation->setPaused(false);
            
            
            if(_mvt.flag() & Movement::Left)
            {
                //_transform.velocity() = _velocity;
                //_transform.velocity().x *= static_cast<Physics::Unit>(-1);
            }
            if(_mvt.flag() & Movement::Right)
            {
                //_transform.velocity() = _velocity;
            }
        }
        
        void Falling::onLeave()
        {
            State::onLeave();
            std::cout << "Falling : onLeave" << std::endl;
        }
        
        void Falling::onChangeSide(const Movement & mvt)
        {
            State::onChangeSide(mvt);
             State * s = _entity->state();
             
            if(_mvt.flag() & Movement::Left)
            {
                //s->transformation().velocity() = _velocity;
                //s->transformation().velocity().x *= static_cast<Physics::Unit>(-1);
                //s->transformation().velocity().y=_transform.velocity().y;
            }
            if(_mvt.flag() & Movement::Right)
            {
                //s->transformation().velocity() = _velocity;
                //s->transformation().velocity().y=_transform.velocity().y;
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
            _velocity=value;      
        }
        
    }
}
