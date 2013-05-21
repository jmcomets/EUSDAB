#include <states/crouch.h>

namespace EUSDAB
{
    namespace States
    {
        Crouch::Crouch(Movement const & m):
            State(m)
        {
        }

        Crouch::~Crouch()
        {
        }

        void Crouch::onUp(const Event & e)
        {
            State::onUp(e);
        }

        void Crouch::onDown(const Event & e)
        {
            State::onDown(e);
            
            if (e.edge == Event::FallingEdge)
            {
                switchState(Movement::Idle || _mvt.direction());
            }
            
        }

        void Crouch::onLeft(const Event & e)
        {
            State::onLeft(e);
            if ((e.edge == Event::RisingEdge))
            {
                onChangeSide(Movement::Crouch | Movement::Left);
                setNextStateAnimationFrameToCurrentFrame();
            }
        }

        void Crouch::onRight(const Event & e)
        {
            State::onRight(e);
            if (e.edge == Event::RisingEdge)
            {
                onChangeSide(Movement::Crouch | Movement::Right);
                setNextStateAnimationFrameToCurrentFrame();
            }
        }

        void Crouch::onNextFrame()
        {
            State::onNextFrame();
        }
        
        void Crouch::onAnimationEnd()
        {
            _animation->setPaused();
            _animation->explicitAdvance(-1);
        }
        
        void Crouch::setNextStateAnimationFrameToCurrentFrame() const
        {
            // Continue animation from current frame in next state
            State * s = _entity->state();
            if (s == nullptr) { return; }

            Animation * a = s->animation();
            if (a == nullptr) { return; }
            a->setCurrentFrame(_animation->currentFrame());
        }
    }
}
