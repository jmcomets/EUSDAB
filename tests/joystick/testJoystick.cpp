#include "testJoystick.h"
#include <SFML/Window/Event.hpp>
#include <movement.h>
#include <iostream>
#include <map>
#include <input/keyboardmapping.h>
#include <input/joystickmapping.h>
#include <entityparser.h>


namespace EUSDAB
{
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
        Entity * player2 = entityParser.loadEntity("../../assets/entities/rickhard");
        Entity * player3 = entityParser.loadEntity("../../assets/entities/rickhard");
        Entity * player4 = entityParser.loadEntity("../../assets/entities/rickhard");

        // DEPRECATED
        //player1->state()->animation()->sprite().setPosition(100, 0);
        //player2->state()->animation()->sprite().setPosition(400, 0);
        //player3->state()->animation()->sprite().setPosition(100, 250);
        //player4->state()->animation()->sprite().setPosition(400, 250);

        // Adding players
        _playerList.push_back(player1);
        _playerList.push_back(player2);
        _playerList.push_back(player3);
        _playerList.push_back(player4);
        _painter.addEntity(_playerList.begin(), _playerList.end());

        //_mapping = new Input::KeyboardMapping(_playerList.begin(), _playerList.end());
        _mapping = new Input::JoystickMapping(_playerList.begin(), _playerList.end());

        // Controller creation
        _input = new Input::Controller(_playerList.begin(), _playerList.end(), _mapping);
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
                _input->pushEvent(eventList.begin(), eventList.end());
            }
        }
        //std::cout << "Push event" << std::endl;
        //_input->pushEvent(eventList.begin(), eventList.end());
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
}
