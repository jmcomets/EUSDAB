#include <states/special.h>
#include <cmath>
#include <iostream>

namespace EUSDAB
{
    namespace States
    {
        Special::Special(Movement const & m):
            State(m)
        {
        }

        Special::~Special()
        {
        }

        void Special::onUp(const Event & e)
        {
            State::onUp(e);
        }

        void Special::onDown(const Event & e)
        {
            State::onDown(e);
        }

        void Special::onLeft(const Event & e)
        {
            State::onLeft(e);

            if(_mvt.flag() & Movement::Up)
            {
                if (e.edge == Event::RisingEdge)
                {
                    std::cout << "Jump : onLeft" << std::endl;
                    _entity->physics().velocity().x = -3;
                    onChangeSide(Movement::Special | Movement::Up | Movement::Left);
                    setNextStateAnimationFrameToCurrentFrame();
                }
                else if(e.edge == Event::FallingEdge)
                {
                    _entity->physics().velocity().x = 0;
                }
            }

        }

        void Special::onRight(const Event & e)
        {
            State::onRight(e);
            if(_mvt.flag() & Movement::Up)
            {
                if (e.edge == Event::RisingEdge)
                {
                    std::cout << "Special : onRight" << std::endl;
                    _entity->physics().velocity().x = 3;
                    onChangeSide(Movement::Special | Movement::Up | Movement::Right);
                    setNextStateAnimationFrameToCurrentFrame();
                }
                else if(e.edge == Event::FallingEdge)
                {
                    _entity->physics().velocity().x = 0;
                }
            }
        }

        void Special::setNextStateAnimationFrameToCurrentFrame() const
        {
            // Continue animation from current frame in next state
            State * s = _entity->state();
            if (s == nullptr) { return; }

            Animation * a = s->animation();
            if (a == nullptr) { return; }
            a->setCurrentFrame(_animation->currentFrame());
        }



        void Special::onNextFrame()
        {
            State::onNextFrame();

            // Shorten code !
            using Physics::Unit;

            static auto trajectoryY = [] (std::time_t t)
            {
                // Be explicit
                const Unit t0 = static_cast<Unit>(t);
                constexpr Unit height = static_cast<Unit>(10.0);
                constexpr Unit time_max = static_cast<Unit>(10.0);

                if (t0 > time_max)
                {
                    return static_cast<Unit>(0);
                }
                return -t0 * height / time_max;
            };

            // Sliding config
            constexpr Unit sliding_ratio = static_cast<Unit>(1.005);
            constexpr Unit sliding_min = static_cast<Unit>(0.01);

            // Sliding code
            _transform.velocity().x /= sliding_ratio;
            if (std::abs(_transform.velocity().x) < sliding_min)
            {
                _transform.velocity().x = static_cast<Unit>(0);
            }

            if ((_mvt.flag() & Movement::Left
                    || _mvt.flag() & Movement::Right)
                    && !(_mvt.flag() & Movement::Idle))
            {
                _transform.velocity().y = trajectoryY(_time);
            }
            if(_mvt.flag() & Movement::Up)
            {
                //_entity->physics().acceleration().y *= 0.85;
            }
        }

        void Special::onAnimationEnd()
        {
            State::onAnimationEnd();
            Movement newMvt(_mvt);
            newMvt.setAction(Movement::Falling);
            //switchState(newMvt);
            //Reset acceleration of upB
            _entity->physics().acceleration().y =  0;
            _entity->setGravitable(true);
            switchState(newMvt & ~Movement::Up & ~Movement::Down);
        }

        void Special::onGround(const Event & e)
        {
            State::onGround(e);
        }
        
        void Special::onEnter()
        {
            State::onEnter();
            //_entity->physics().velocity().y = 0.1;
            std::cout << "Special : onEnter velocity = " << _entity->physics().velocity().y << std::endl;
            if(_mvt.flag() & Movement::Up)
            {
                _entity->physics().velocity().y = -5;
                 //_entity->physics().acceleration().y = 0;
                 _entity->setGravitable(false);
            }
        }
        
        void Special::onLeave()
        {
            State::onLeave();
            _attack->reset();
            _entity->setNbrJump(0);
        }
        
      
    }
}
