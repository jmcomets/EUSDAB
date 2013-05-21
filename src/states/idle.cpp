#include <states/idle.h>
#include <constants.h>

namespace EUSDAB
{
    namespace States
    {
        Idle::Idle():
            State()
        {
            std::cout << "Constructor Idle" << std::endl;
        }

        Idle::~Idle()
        {
        }

        void Idle::onEnter()
        {
            State::onEnter();
            std::cout << "Idle : onEnter" << std::endl;
        }

        void Idle::onLeave()
        {
            State::onLeave();
            std::cout << "Idle : onLeave" << std::endl;
        }

        void Idle::onUp(const Event & e)
        {
            State::onUp(e);
            std::cout << "Idle : OnUp" << std::endl;
            if (e.edge == Event::RisingEdge)
            {
                std::cout << "Canjump : " << entity()->canJump() << " | jumpPossible : " << entity()->jumpPossible() << std::endl;
                if (entity()->canJump() && entity()->jumpPossible())
                {
                    switchState(Movement::Jump | _mvt.direction());
                }
            }

        }

        void Idle::onDown(const Event & e)
        {
            std::cout << "Idle : onDown" << std::endl;
            State::onDown(e);
            if (e.edge == Event::RisingEdge || e.edge == Event::ContinuousEdge)
            {
                //switchState(Movement::Crouch | _mvt.direction());
            }
        }

        void Idle::onLeft(const Event & e)
        {
            State::onLeft(e);
            std::cout << "Idle : Left" << std::endl;
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

        void Idle::onRight(const Event & e)
        {
            State::onRight(e);
            std::cout << "Idle : Right" << std::endl;

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

        void Idle::onA(const Event & e)
        {
            State::onA(e);
            std::cout << "Idle : A" << std::endl;
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

        void Idle::onB(const Event & e)
        {
            std::cout << "Idle : B" << std::endl;
            State::onB(e);
            if (e.edge == Event::RisingEdge)
            {
                switchState(Movement::Special | Movement::Idle | _mvt.direction());
            }
        }

        void Idle::onNextFrame()
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

        void Idle::setSlidingRatio(Physics::Unit value)
        {
            _sliding_ratio=value;
        }
    }
}
