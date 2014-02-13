#include <states/motion.h>

namespace EUSDAB
{
    namespace States
    {
        Motion::Motion(const Movement & m):
            State(m)
        {
        }

        Motion::~Motion()
        {
        }

        void Motion::onA(const Event & e)
        {
            State::onA(e);
            if (e.edge == Event::RisingEdge)
            {
                switchStateWithVelocity(Movement::Attack | _mvt.direction());
            }
        }
        
        void Motion::onB(const Event & e)
        {
            State::onB(e);
            if (e.edge == Event::RisingEdge)
            {
                switchStateWithVelocity(Movement::Special | _mvt.direction());
            }
        }

        void Motion::setVelocity(const Physics::Vector2 & v)
        {
            _velocity = v;
        }
        
        void Motion::onNextFrame()
        {
            State::onNextFrame();
            if (_entity->physics().velocity().y > 0)
            {
                switchStateWithVelocity(Movement::Falling | _mvt.direction());
            }
        }

        void Motion::switchStateWithVelocity(const Movement::Flag & f)
        {
            switchState(f);
            State * s = _entity->state();
            if (s != nullptr)
            {
                s->transformation().velocity() = _velocity;
            }
        }
    }
}
