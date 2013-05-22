#include <states/idle.h>
#include <constants.h>

namespace EUSDAB
{
    namespace States
    {
        Idle::Idle(Movement const & m):
            State(m)
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
            _entity->physics().velocity().x = 0;
        }

        void Idle::onLeave()
        {
            State::onLeave();
            std::cout << "Idle : onLeave" << std::endl;
        }

        void Idle::onUp(const Event & e)
        {
            State::onUp(e);
            //std::cout << "Idle : OnUp" << std::endl;
            if (e.edge == Event::RisingEdge)
            {
                //std::cout << "Canjump : " << entity()->canJump() << " | jumpPossible : " << entity()->jumpPossible() << std::endl;
                if (entity()->canJump() && entity()->jumpPossible())
                {
                    switchState(Movement::Jump | _mvt.direction());
                }
            }

        }

        void Idle::onTrigger(const Event & e)
        {
            State::onTrigger(e);
            //std::cout << "Idle : OnTrigger" << std::endl;
            if (e.edge == Event::RisingEdge)
            {
				switchState(Movement::Guard | _mvt.direction());
            }

        }

        void Idle::onDown(const Event & e)
        {
            //std::cout << "Idle : onDown" << std::endl;
            State::onDown(e);
            if (e.edge == Event::RisingEdge)
            {
                switchState(Movement::Crouch | _mvt.direction());
            }
        }

        void Idle::onLeft(const Event & e)
        {
            State::onLeft(e);
            //std::cout << "Idle : Left" << std::endl;
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
            //std::cout << "Idle : Right" << std::endl;

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
            //std::cout << "Idle : A" << std::endl;
            if ((e.edge == Event::RisingEdge))
            {
                if(_entity->_verticalState == Entity::VerticalState::Middle)
                {
                    switchState(Movement::Attack | _mvt.direction());
                }
                else if(_entity->_verticalState == Entity::VerticalState::Up)
                {
                    switchState(Movement::Attack | Movement::Up | _mvt.direction());
                }
                else if(_entity->_verticalState == Entity::VerticalState::Down)
                {
                    switchState(Movement::Attack | Movement::Down | _mvt.direction());
                }
            }
        }

        void Idle::onB(const Event & e)
        {
            //std::cout << "Idle : B" << std::endl;
            State::onB(e);
            if (e.edge == Event::RisingEdge)
            {
                if(_entity->_verticalState == Entity::VerticalState::Middle)
                {
                    switchState(Movement::Special | Movement::Idle | _mvt.direction());
                }
                else if(_entity->_verticalState == Entity::VerticalState::Up)
                {
                    auto s = _entity->state();
                    if(s != nullptr)
                    {
                        std::cout << "" << std::endl;
                        s->transformation().velocity().y =  -100.0;
                        _entity->physics().acceleration().y =  -0.60;
                        std::cout << "Idle : onB | onUp  velocity = " << _entity->physics().velocity().y << std::endl;
                    }
                    switchState(Movement::Special | Movement::Up | _mvt.direction());
                }
                else if(_entity->_verticalState == Entity::VerticalState::Down)
                {
                    switchState(Movement::Special | Movement::Down | _mvt.direction());
                }
            }
        }

        void Idle::onNextFrame()
        {
            State::onNextFrame();

            if(_entity->physics().velocity().y > 0)
            {
                switchState(Movement::Falling | _mvt.direction());
            }
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
