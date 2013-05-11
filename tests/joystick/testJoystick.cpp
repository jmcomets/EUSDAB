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
        //Entity * player1 = new Entity();
        //Entity * player2 = entityParser.loadEntity("../../assets/entities/rickhard2");
        //Entity * player2 = new Entity();
        
        if (player1 == nullptr)
        {
            throw std::runtime_error("Entity wasn't loaded");
        }
        std::cout << "Loaded Entity " << player1->name() << std::endl;
        //std::cout << "Loaded Entity " << player2->name() << std::endl;

        //player2->state()->animation.sprite()->setPosition(300, 250);
        _painter.addEntity(player1);
        //_painter.addEntity(player2);


        // Adding players
        _playerList.emplace_back(player1);
        //_playerList.emplace_back(player2);

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
}
