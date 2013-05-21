#include <states/stunned.h>
#include <constants.h>

namespace EUSDAB
{
    namespace States
    {
        Stunned::Stunned(Movement const & m):
            State(m)
        {
            std::cout << "Constructor Stunned" << std::endl;
        }

        Stunned::~Stunned()
        {
        }

        void Stunned::onEnter()
        {
            State::onEnter();
            std::cout << "Stunned : onEnter" << std::endl;
        }

        void Stunned::onLeave()
        {
            State::onLeave();
            std::cout << "Stunned : onLeave" << std::endl;
        }

        void Stunned::onUp(const Event & e)
        {
            State::onUp(e);
            

        }

        void Stunned::onDown(const Event & e)
        {
            std::cout << "Stunned : onDown" << std::endl;
            State::onDown(e);
            
        }

        void Stunned::onLeft(const Event & e)
        {
            State::onLeft(e);
            std::cout << "Stunned : Left" << std::endl;
            
        }

        void Stunned::onRight(const Event & e)
        {
            State::onRight(e);
            std::cout << "Stunned : Right" << std::endl;

            
        }

        void Stunned::onA(const Event & e)
        {
            State::onA(e);
            std::cout << "Stunned : A" << std::endl;
            
        }

        void Stunned::onB(const Event & e)
        {
            std::cout << "Stunned : B" << std::endl;
            State::onB(e);
        }

        void Stunned::onNextFrame()
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
        
        void Stunned::onAnimationEnd()
        {
            State::onAnimationEnd();
            Movement newMvt(_mvt);
            newMvt.setAction(Movement::Idle);
            switchState(newMvt);
        }

        
    }
}
