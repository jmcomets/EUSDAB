#include "testinput.h"
#include <movement.h>
#include <iostream>
#include <input/keyboardmapping.h>
#include <input/joystickmapping.h>

namespace EUSDAB
{
    namespace Priv
    {
        static std::size_t uniqueId()
        {
            static std::size_t id = 0;
            return id++;
        }
    }

    InputTest::InputTest(sf::RenderWindow & window):
        Application(window),
        _playerList(),
        _input(nullptr),
        _mapping()
    {
        // Creating players
        Entity * player1 = new Entity();
        Entity * player2 = new Entity();

        // InputTestState state bundle
        Movement testMovement(Movement::Idle | Movement::Left);
        InputTestState * player1testState = new InputTestState(testMovement);
        InputTestState * player2testState = new InputTestState(testMovement);

        // Adding player states
        player1->addState(player1testState);
        player2->addState(player2testState);

        // Setting player states
        player1->setState(testMovement);
        player2->setState(testMovement);

        // Adding players
        _playerList.emplace_back(player1);
        _playerList.emplace_back(player2);

        //_mapping = new Input::KeyboardMapping(_playerList.begin(), _playerList.end());
        _mapping = new Input::JoystickMapping(_playerList.begin(), _playerList.end());

        // Controller creation
        _input = new Input::Controller(_playerList.begin(), _playerList.end(), _mapping);
    }

    InputTest::~InputTest()
    {
        // Controller delete
        delete _input;

        // Entities delete
        for (auto p : _playerList)
        {
            delete p;
        }
    }

    void InputTest::event()
    {
        sf::Event e;
        std::vector<sf::Event> eventList;
        while (_window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                _window.close();
            }
            else if (e.type == sf::Event::KeyPressed)
            {
                std::cout << "Key pressed" << std::endl;
                eventList.push_back(e);
            }
            else if (e.type == sf::Event::KeyReleased)
            {
                std::cout << "Key released" << std::endl;
                eventList.push_back(e);
            }
            else if(e.type == sf::Event::JoystickButtonPressed
                    || e.type == sf::Event::JoystickMoved)
            {
                eventList.push_back(e);
            }
        }
        std::cout << "Push event" << std::endl;
        _input->pushEvent(eventList.begin(), eventList.end());
        std::cout << "Event pushed" << std::endl;
        _input->nextFrame();
        std::cout << "Next frame" << std::endl;
    }

    void InputTest::update()
    {
        _input->update();
    }

    InputTestState::InputTestState(const Movement & mvt):
        State(mvt),
        _x(0), _y(0),
        _id(Priv::uniqueId())
    {
    }

    InputTestState::~InputTestState()
    {
    }

    void InputTestState::onUp(const Event & e)
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

    void InputTestState::onDown(const Event & e)
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

    void InputTestState::onLeft(const Event & e)
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

    void InputTestState::onRight(const Event & e)
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

    void InputTestState::onNextFrame()
    {
        State::onNextFrame();
        std::cout << "[" << _id << "] - " << "[NEXT] - Heure " 
            << _time << std::endl;
    }
}
