#include <states/test.h>
#include <iostream>

namespace EUSDAB
{
    namespace States
    {
        namespace Priv
        {
            static std::size_t uniqueId()
            {
                static std::size_t id = 0;
                return id++;
            }
        }

        Test::Test():
            State(),
            _x(0), _y(0),
            _id(Priv::uniqueId())
        {
        }

        Test::~Test()
        {
        }

        void Test::onUp(const Event & e)
        {
            State::onUp(e);
            std::cout << "[" << _id << "] - " << "UP - ";
            if (e.edge == Event::RisingEdge)
            {
                _y += e.ratio;
                std::cout << "MONTANT";
            }
            else if (e.edge == Event::FallingEdge)
            {
                std::cout << "DESCENDANT";
            }
            else if (e.edge == Event::ContinuousEdge)
            {
                std::cout << "CONTINU";
            }
            std::cout << " - " << e.ratio << " " << _y << std::endl;
        }

        void Test::onDown(const Event & e)
        {
            State::onDown(e);
            std::cout << "[" << _id << "] - " << "DOWN - ";
            if (e.edge == Event::RisingEdge)
            {
                _y -= e.ratio;
                std::cout << "MONTANT";
            }
            else if (e.edge == Event::FallingEdge)
            {
                std::cout << "DESCENDANT";
            }
            else if (e.edge == Event::ContinuousEdge)
            {
                std::cout << "CONTINU";
            }
            std::cout << " - " << e.ratio << " " << _y << std::endl;
        }

        void Test::onLeft(const Event & e)
        {
            State::onLeft(e);
            std::cout << "[" << _id << "] - " << "LEFT - ";
            if (e.edge == Event::RisingEdge)
            {
                _x += e.ratio;
                std::cout << "MONTANT";
            }
            else if (e.edge == Event::FallingEdge)
            {
                std::cout << "DESCENDANT";
            }
            else if (e.edge == Event::ContinuousEdge)
            {
                std::cout << "CONTINU";
            }
            std::cout << " - " << e.ratio << " " << _x << std::endl;
        }

        void Test::onRight(const Event & e)
        {
            State::onRight(e);
            std::cout << "[" << _id << "] - " << "RIGHT - ";
            if (e.edge == Event::RisingEdge)
            {
                _x += e.ratio;
                std::cout << "MONTANT";
            }
            else if (e.edge == Event::FallingEdge)
            {
                std::cout << "DESCENDANT";
            }
            else if (e.edge == Event::ContinuousEdge)
            {
                std::cout << "CONTINU";
            }
            std::cout << " - " << e.ratio << " " << _x << std::endl;
        }

        void Test::onNextFrame()
        {
            State::onNextFrame();
            std::cout << "[" << _id << "] - " << "[NEXT] - Heure " 
                << _time << std::endl;
        }
    }
}
