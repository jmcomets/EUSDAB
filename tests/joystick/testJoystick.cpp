#include "testJoystick.h"
#include <SFML/Window/Event.hpp>
#include <movement.h>
#include <iostream>
#include <map>
#include <input/keyboardmapping.h>
#include <input/joystickmapping.h>
#include <entityparser.h>
#include "painter.h"


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


    JoystickTest::JoystickTest(sf::RenderWindow & window):
        Application(window),
        _playerList(),
        _input(nullptr),
        _mapping(),
        _painter(window)
    {
        EntityParser entityParser;

        // Creating players
        Entity * player1 = entityParser.loadEntity("../../assets/entities/rickhard");
        //Entity * player1 = new Entity();
        //Entity * player2 = entityParser.loadEntity("../../assets/entities/rickhard2");
        
        if (player1 == nullptr/* || player2 == nullptr*/)
        {
            throw std::runtime_error("Entity wasn't loaded");
        }
        std::cout << "Loaded Entity " << player1->name() << std::endl;
        //std::cout << "Loaded Entity " << player2->name() << std::endl;

        //player2->state()->animation.sprite()->setPosition(300, 250);
        _painter.addEntity(player1);
        //_painter.addEntity(player2);


        // JoystickTestState state bundle
        //Movement testMovement(Movement::Idle | Movement::Left);
        //JoystickTestState * player1testState = new JoystickTestState();
        //player1testState->setMovement(testMovement);
        //JoystickTestState * player2testState = new JoystickTestState();
        //player2testState->setMovement(testMovement);

        // Adding player states
        //player1->addState(player1testState);
        //player2->addState(player2testState);

        // Setting player states
        //player1->setState(testMovement);
        //player2->setState(testMovement);

        //Loading sprites

        // Adding players
        _playerList.emplace_back(player1);
        //_playerList.emplace_back(player2);

        //_mapping = new Input::KeyboardMapping(_playerList.begin(), _playerList.end());
        _mapping = new Input::JoystickMapping(_playerList.begin(), _playerList.end());

        // Controller creation
        _input = new Input::Controller(_playerList.begin(), _playerList.end(), _mapping);
        //_input = new Input::Controller(_playerList.begin() + 1, _playerList.end(), _mapping);
        //_input = new Input::Controller(_playerList.begin(), _playerList.end() - 1, _mapping);
    }

    JoystickTest::~JoystickTest()
    {
    // Controller delete
        delete _input;
        delete _mapping;

        // Entities delete
        for (auto p : _playerList)
        {
            delete p;
        }
    }

    void JoystickTest::event()
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
        //std::cout << "Push event" << std::endl;
        _input->pushEvent(eventList.begin(), eventList.end());
        //std::cout << "Event pushed" << std::endl;
        _input->nextFrame();
        //std::cout << "Next frame" << std::endl;
    }

    void JoystickTest::update()
    {
        _input->update();
    }

    void JoystickTest::render()
    {
        _painter.draw();
    }

//*****************************************************************************
    JoystickTestState::JoystickTestState():
        State(),
        _x(0), _y(0),
        _id(Priv::uniqueId())
    {
    }

    JoystickTestState::~JoystickTestState()
    {
    }

    void JoystickTestState::onUp(const Event & e)
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

    void JoystickTestState::onDown(const Event & e)
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

    void JoystickTestState::onLeft(const Event & e)
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

    void JoystickTestState::onRight(const Event & e)
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

    void JoystickTestState::onA(Event const & e)
    {
        State::onA(e);
        std::cout << "[" << _id << "] - " << "A- ";
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

    void JoystickTestState::onB(Event const & e)
    {
        State::onB(e);
        std::cout << "[" << _id << "] - " << "B- ";
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

    void JoystickTestState::onX(Event const & e)
    {
        State::onX(e);
        std::cout << "[" << _id << "] - " << "X- ";
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

    void JoystickTestState::onY(Event const & e)
    {
        State::onY(e);
        std::cout << "[" << _id << "] - " << "Y- ";
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

    void JoystickTestState::onZ(Event const & e)
    {
        State::onZ(e);
        std::cout << "[" << _id << "] - " << "Z- ";
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

    void JoystickTestState::onTrigger(Event const & e)
    {
        State::onTrigger(e);
        std::cout << "[" << _id << "] - " << "Trigger- ";
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



    void JoystickTestState::onNextFrame()
    {
        State::onNextFrame();
        //std::cout << "[" << _id << "] - " << "[NEXT] - Heure " 
            //<< _time << std::endl;
    }
}
