#include <states/aerialDodge.h>
#include <constants.h>

namespace EUSDAB
{
    namespace States
    {
        AerialDodge::AerialDodge(Movement const & m):
            State(m),
            _velocity(0,0)
        {
        }

        AerialDodge::~AerialDodge()
        {
        }

        void AerialDodge::onUp(const Event & e)
        {
            State::onUp(e);
            

        }
        
        void AerialDodge::onTrigger(const Event & e)
        {
            State::onTrigger(e);
            
        }

        void AerialDodge::onDown(const Event & e)
        {
            State::onDown(e);
            
            
        }

        void AerialDodge::onLeft(const Event & e)
        {
            State::onLeft(e);
            
        }

        void AerialDodge::onRight(const Event & e)
        {
            State::onRight(e);
           
        }
        
        void AerialDodge::onA(const Event & e)
        {
            State::onA(e);
            
        }
        
        void AerialDodge::onB(const Event & e)
        {
            State::onB(e);
            if (e.edge == Event::RisingEdge)
            {
                switchState(Movement::Special | Movement::Idle | _mvt.direction());
            }
        }

        void AerialDodge::onNextFrame()
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
        
        void AerialDodge::setVelocity(const  Physics::Vector2 & value)
        {
            _velocity=value;      
        }
        
        void AerialDodge::onAnimationEnd()
        {
            State::onAnimationEnd();
            Movement newMvt(_mvt);
            newMvt.setAction(Movement::Falling);
            switchState(newMvt);
        }
    }
}
