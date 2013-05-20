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
        }

        void Falling::onDown(const Event & e)
        {
            State::onDown(e);
        }

        void Falling::onLeft(const Event & e)
        {
            State::onLeft(e);
            if (e.edge == Event::RisingEdge || e.edge == Event::ContinuousEdge)
            {
                onChangeSide(Movement::Falling | Movement::Left);
            }
            else
            {
                //switchState(Movement::Falling | Movement::Idle | Movement::Left);
            }
        }

        void Falling::onRight(const Event & e)
        {
            State::onRight(e);
            if (e.edge == Event::RisingEdge || e.edge == Event::ContinuousEdge)
            {
                onChangeSide(Movement::Falling | Movement::Right);
            }
            else
            {
                //switchState(Movement::FallingIdle | Movement::Right);
            }
        }

        void Falling::onGround(const Event & e)
        {
            State::onGround(e);
            if (e.edge == Event::RisingEdge || e.edge == Event::ContinuousEdge)
            {
                switchState(Movement::Idle | _mvt.direction());
            }
        }



        void Falling::onNextFrame()
        {
            State::onNextFrame();
        }
        
        void Falling::onEnter()
        {
            // TODO add vertical impulse

            _animation->setPaused(false);
            
            //FIXME
            _speedY = 0;
            _speedX = 1.;
            if(_mvt.flag() & Movement::Left)
                _transform.velocity() = Physics::Vector2(-_speedX , _speedY);
            if(_mvt.flag() & Movement::Right)
                _transform.velocity() = Physics::Vector2(_speedY, _speedY);
        }
        
        void Falling::onChangeSide(const Movement & mvt)
        {
            State::onChangeSide(mvt);
             State * s = _entity->state();
             
            if(_mvt.flag() & Movement::Left)
                 s->transformation().velocity() = Physics::Vector2(-_speedX , _transform.velocity().y);
            if(_mvt.flag() & Movement::Right)
                 s->transformation().velocity() = Physics::Vector2(_speedY, _transform.velocity().y);
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
        
        void Falling::setSpeed(Physics::Unit X,Physics::Unit Y)
        {
            _speedX=X;
            _speedY=Y;        
        }
        
    }
}
