#include <states/dodge.h>
#include <constants.h>

namespace EUSDAB
{
    namespace States
    {
        Dodge::Dodge():
            State()
        {
        }

        Dodge::~Dodge()
        {
        }

        void Dodge::onUp(const Event & e)
        {
            State::onUp(e);
            if (e.edge == Event::RisingEdge)
            {
                if (entity()->canJump()&&entity()->jumpPossible())
                {
                    switchState(Movement::Jump | _mvt.direction());
                }
            }

        }
        
        void Dodge::onTrigger(const Event & e)
        {
            if (e.edge == Event::RisingEdge)
            {
                switchState(Movement::Guard | _mvt.direction()); 
            }
        }

        void Dodge::onDown(const Event & e)
        {
            State::onDown(e);
            if (e.edge == Event::RisingEdge || e.edge == Event::ContinuousEdge)
            {
                //switchState(Movement::Crouch | _mvt.direction());
            }
        }

        void Dodge::onLeft(const Event & e)
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

        void Dodge::onRight(const Event & e)
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
        
        void Dodge::onA(const Event & e)
        {
            State::onA(e);
            if ((e.edge == Event::RisingEdge))
            {
                if (_mvt.flag() & Movement::Left)
                {
                    switchState(Movement::Attack | Movement::Left);
                }
                else if (_mvt.flag() & Movement::Right)
                {
                    switchState(Movement::Attack | Movement::Right);
                }
                else
                {
                    //switchState(Movement::Attack | Movement::Left);
                }
            }
        }
        
        void Dodge::onB(const Event & e)
        {
            State::onB(e);
            if (e.edge == Event::RisingEdge)
            {
                switchState(Movement::Special | Movement::Idle | _mvt.direction());
            }
        }

        void Dodge::onNextFrame()
        {
            State::onNextFrame();

            //// Shorten code !
            //using Physics::Unit;

            //// Sliding config
            //constexpr Unit sliding_min = static_cast<Unit>(0.01);

            //// Sliding code
            //_transform.velocity().x /= _sliding_ratio;
            //if (std::abs(_transform.velocity().x) < sliding_min)
            //{
                //_transform.velocity().x = static_cast<Unit>(0);
            /*}*/
        }
        
        void Dodge::setVelocity(const  Physics::Vector2 & value)
        {
            _velocity=value;      
        }
    }
}
