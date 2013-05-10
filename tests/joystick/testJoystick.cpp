#include "testJoystick.h"
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <map>

namespace EUSDAB
{
    JoystickTest::JoystickTest(sf::RenderWindow & window):
        Application(window)
    {
        
    }

    JoystickTest::~JoystickTest()
    {
    }

    void JoystickTest::event()
    {
        std::map<sf::Joystick::Axis, std::pair<std::string, bool (*)(float const &)>> axis;
        axis[sf::Joystick::X] = std::make_pair("x", [](float const & x) { return std::abs(x) > 20; });
        axis[sf::Joystick::Y] = std::make_pair("y", [](float const & x) { return std::abs(x) > 20; });
        axis[sf::Joystick::Z] = std::make_pair("z", [](float const & x) { return x > -98; });
        axis[sf::Joystick::R] = std::make_pair("r", [](float const & x) { return std::abs(x) > 20; });
        axis[sf::Joystick::U] = std::make_pair("u", [](float const & x) { return std::abs(x) > 20; });
        axis[sf::Joystick::V] = std::make_pair("v", [](float const & x) { return std::abs(x) > 20; });
        axis[sf::Joystick::PovX] = std::make_pair("povX", [](float const & x) { return std::abs(x) > 20; });
        axis[sf::Joystick::PovY] = std::make_pair("povY", [](float const & x) { return std::abs(x) > 20; });
        sf::Event e;
        while (_window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                _window.close();
            }
            else if (e.type == sf::Event::JoystickMoved)
            {
                for(auto it = axis.begin(); it != axis.end(); ++it)
                {
                    if(sf::Joystick::hasAxis(e.joystickButton.joystickId, it->first))
                    {
                        if(e.joystickMove.axis == it->first)
                        {
                            float x = sf::Joystick::getAxisPosition(e.joystickButton.joystickId, it->first);
                            if(it->second.second(x))
                            {
                                std::cout << it->second.first << " : " << x << std::endl;
                            }
                            break;
                        }
                    }
                }
            }
            else if(e.type == sf::Event::JoystickButtonPressed)
            {
                if(sf::Joystick::isConnected(0))
                {
                    std::cout << "joystick id: " << e.joystickButton.joystickId << std::endl;
                    std::cout << "button: " << e.joystickButton.button << std::endl;
                }
            }

        }
    }

    void JoystickTest::update()
    {
        //_entity->state()->onNextFrame();
    }

    void JoystickTest::render()
    {
        //_painter.draw();
    }
}
