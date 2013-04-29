#include <states/test.h>
#include <iostream>

namespace EUSDAB
{
    namespace States
    {
        Test::Test():
            State(), _n(0)
        {
        }

        Test::~Test()
        {
        }

        void Test::onUp(const Event & e)
        {
            if (e.edge == Event::RisingEdge)
            {
                _n += e.ratio;
                std::cout << "[UP] - Montant - " << e.ratio << " " << _n << std::endl;
            }
            else if (e.edge == Event::FallingEdge)
            {
                std::cout << "[UP] - Descendant - " << e.ratio << " " << _n << std::endl;
            }
            else if (e.edge == Event::ContinuousEdge)
            {
                std::cout << "[UP] - Continue - " << e.ratio << " " << _n << std::endl;
            }
        }

        void Test::onDown(const Event & e)
        {
            if (e.edge == Event::RisingEdge)
            {
                _n -= e.ratio;
                std::cout << "[DOWN] - Montant - " << e.ratio << " " << _n << std::endl;
            }
            else if (e.edge == Event::FallingEdge)
            {
                std::cout << "[DOWN] - Descendant - " << e.ratio << " " << _n << std::endl;
            }
            else if (e.edge == Event::ContinuousEdge)
            {
                std::cout << "[DOWN] - Continue - " << e.ratio << " " << _n << std::endl;
            }
        }

        void Test::onLeft(const Event & e)
        {
            if (e.edge == Event::RisingEdge)
            {
                std::cout << "[LEFT] - Montant - " << e.ratio << std::endl;
            }
            else if (e.edge == Event::FallingEdge)
            {
                std::cout << "[LEFT] - Descendant - " << e.ratio << std::endl;
            }
            else if (e.edge == Event::ContinuousEdge)
            {
                std::cout << "[LEFT] - Continue - " << e.ratio << std::endl;
            }
        }

        void Test::onRight(const Event & e)
        {
            if (e.edge == Event::RisingEdge)
            {
                std::cout << "[RIGHT] - Montant - " << e.ratio << std::endl;
            }
            else if (e.edge == Event::FallingEdge)
            {
                std::cout << "[RIGHT] - Descendant - " << e.ratio << std::endl;
            }
            else if (e.edge == Event::ContinuousEdge)
            {
                std::cout << "[RIGHT] - Continue - " << e.ratio << std::endl;
            }
        }
    }
}
