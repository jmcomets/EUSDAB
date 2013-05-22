#include <states/shieldBreak.h>
#include <constants.h>

namespace EUSDAB
{
    namespace States
    {
        ShieldBreak::ShieldBreak(Movement const & m):
            State(m)
        {
            std::cout << "Constructor ShieldBreak" << std::endl;
        }

        ShieldBreak::~ShieldBreak()
        {
        }

        void ShieldBreak::onEnter()
        {
            State::onEnter();
            std::cout << "ShieldBreak : onEnter" << std::endl;
        }

        void ShieldBreak::onLeave()
        {
            State::onLeave();
            std::cout << "ShieldBreak : onLeave" << std::endl;
        }

        void ShieldBreak::onUp(const Event & e)
        {
            State::onUp(e);
            

        }

        void ShieldBreak::onDown(const Event & e)
        {
            std::cout << "ShieldBreak : onDown" << std::endl;
            State::onDown(e);
            
        }

        void ShieldBreak::onLeft(const Event & e)
        {
            State::onLeft(e);
            std::cout << "ShieldBreak : Left" << std::endl;
            
        }

        void ShieldBreak::onRight(const Event & e)
        {
            State::onRight(e);
            std::cout << "ShieldBreak : Right" << std::endl;

            
        }

        void ShieldBreak::onA(const Event & e)
        {
            State::onA(e);
            std::cout << "ShieldBreak : A" << std::endl;
            
        }

        void ShieldBreak::onB(const Event & e)
        {
            std::cout << "ShieldBreak : B" << std::endl;
            State::onB(e);
        }

        void ShieldBreak::onNextFrame()
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
        
        void ShieldBreak::onAnimationEnd()
        {
            State::onAnimationEnd();
            Movement newMvt(_mvt);
            newMvt.setAction(Movement::Stunned);
            switchState(newMvt);
        }

        
    }
}
