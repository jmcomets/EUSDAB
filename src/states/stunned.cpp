#include <states/stand.h>
#include <constants.h>

namespace EUSDAB
{
    namespace States
    {
        Stand::Stand(Movement const & m):
            State(m)
        {
            std::cout << "Constructor Stand" << std::endl;
        }

        Stand::~Stand()
        {
        }

        void Stand::onEnter()
        {
            State::onEnter();
            std::cout << "Stand : onEnter" << std::endl;
        }

        void Stand::onLeave()
        {
            State::onLeave();
            std::cout << "Stand : onLeave" << std::endl;
        }

        void Stand::onUp(const Event & e)
        {
            State::onUp(e);
            

        }

        void Stand::onDown(const Event & e)
        {
            std::cout << "Stand : onDown" << std::endl;
            State::onDown(e);
            
        }

        void Stand::onLeft(const Event & e)
        {
            State::onLeft(e);
            std::cout << "Stand : Left" << std::endl;
            
        }

        void Stand::onRight(const Event & e)
        {
            State::onRight(e);
            std::cout << "Stand : Right" << std::endl;

            
        }

        void Stand::onA(const Event & e)
        {
            State::onA(e);
            std::cout << "Stand : A" << std::endl;
            
        }

        void Stand::onB(const Event & e)
        {
            std::cout << "Stand : B" << std::endl;
            State::onB(e);
        }

        void Stand::onNextFrame()
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

        
    }
}
