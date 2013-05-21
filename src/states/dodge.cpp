#include <states/dodge.h>
#include <constants.h>

namespace EUSDAB
{
    namespace States
    {
        Dodge::Dodge(Movement const & m):
            State(m),
            _velocity(0,0)
        {
        }

        Dodge::~Dodge()
        {
        }

        void Dodge::onUp(const Event & e)
        {
            State::onUp(e);

        }
        
        void Dodge::onTrigger(const Event & e)
        {
            State::onTrigger(e);
        }

        void Dodge::onDown(const Event & e)
        {
            State::onDown(e);
        }

        void Dodge::onLeft(const Event & e)
        {
            State::onLeft(e);
        }

        void Dodge::onRight(const Event & e)
        {
            State::onRight(e);
            
        }
        
        void Dodge::onA(const Event & e)
        {
            State::onA(e);
        }
        
        void Dodge::onB(const Event & e)
        {
            State::onB(e);
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
        
        void Dodge::onAnimationEnd()
        {
            State::onAnimationEnd();
            Movement newMvt(_mvt);
            newMvt.setAction(Movement::Idle);
            switchState(newMvt & ~Movement::Up & ~Movement::Down);
        }
    }
}
