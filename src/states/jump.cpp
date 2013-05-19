#include <states/jump.h>
#include <iostream>

namespace EUSDAB
{
    namespace States
    {
        Jump::Jump():
            State()
        {
        }

        Jump::~Jump()
        {
        }

        void Jump::onUp(const Event & e)
        {
            State::onUp(e);
        }

        void Jump::onDown(const Event & e)
        {
            State::onDown(e);
            if (e.edge == Event::RisingEdge)
            {
                switchState(Movement::Falling | _mvt.direction());
            }
        }

        void Jump::onGround(const Event & e)
        {
            State::onGround(e);
            if (e.edge == Event::RisingEdge)
            {
                switchState(Movement::Idle | _mvt.direction());
            }
        }

        void Jump::onLeft(const Event & e)
        {
            State::onLeft(e);

            if (e.edge == Event::RisingEdge || e.edge == Event::ContinuousEdge)
            {
                onChangeSide(Movement::Jump | Movement::Left);
                setNextStateAnimationFrameToCurrentFrame();
            }
            else
            {
                //switchState(Movement::Jump | Movement::Idle | Movement::Left);
            }
        }

        void Jump::onRight(const Event & e)
        {
            State::onRight(e);

            if (e.edge == Event::RisingEdge || e.edge == Event::ContinuousEdge)
            {
                onChangeSide(Movement::Jump | Movement::Right);
                setNextStateAnimationFrameToCurrentFrame();
            }
            else
            {
                //switchState(Movement::Jump | Movement::Idle | Movement::Right);
            }
        }

        void Jump::onNextFrame()
        {
            State::onNextFrame();

            // Shorten code !
            using Physics::Unit;

            static auto trajectoryY = [] (std::time_t t)
            {
                // Be explicit
                const Unit t0 = static_cast<Unit>(t);
                constexpr Unit height = static_cast<Unit>(40.0);
                constexpr Unit time_max = static_cast<Unit>(17.0);

                if (t0 > time_max)
                {
                    return static_cast<Unit>(0);
                }
                return -t0 * height / time_max;
            };

            if (_transform.velocity().y<0)
            {
                switchState(Movement::Falling | _mvt.direction());
            }
            
            if (_transform.velocity().y<(_jumpValue/2))
            {
                entity()->setJumpPossible(true);
            }
        }
        
       
        
        void Jump::onEnter()
        {
            // TODO add vertical impulse
            _animation->setPaused(false);
            entity()->setJumpPossible(false);
            entity()->setNbrJump(entity()->nbrJump()-1);
            
            _transform.velocity().y = 4;
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
        
        void Jump::onMiddleOfJump()
        {
        
        }
        
        
        void Jump::onJumpEnd()
        {
        
        }
    }
}
