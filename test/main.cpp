#include <SFML/Window.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "EUSDAB");
    sf::Text xAxis("X axis : ");
    sf::Text xAxisValue("");
    sf::Text yAxis("Y axis : ");
    sf::Text yAxisValue("");
    sf::Text zAxis("Z axis : ");
    sf::Text zAxisValue("");
    sf::Text rAxis("R axis : ");
    sf::Text rAxisValue("");
    sf::Text uAxis("U axis : ");
    sf::Text uAxisValue("");
    sf::Text vAxis("V axis : ");
    sf::Text vAxisValue("");
    sf::Text povXAxis("povX axis : ");
    sf::Text povXAxisValue("");
    sf::Text povYAxis("povY axis : ");
    sf::Text povYAxisValue("");
    sf::Text btn("Button pressed : ");
    sf::Text btnValue("");

    xAxis.setPosition(10, 10);
    xAxisValue.setPosition(xAxis.getGlobalBounds().width + 20, 10);

    yAxis.setPosition(10, 35);
    yAxisValue.setPosition(yAxis.getGlobalBounds().width + 20, 35);

    zAxis.setPosition(10, 60);
    zAxisValue.setPosition(zAxis.getGlobalBounds().width + 20, 60);

    rAxis.setPosition(10, 85);
    rAxisValue.setPosition(rAxis.getGlobalBounds().width + 20, 85);

    uAxis.setPosition(10, 110);
    uAxisValue.setPosition(uAxis.getGlobalBounds().width + 20, 110);

    vAxis.setPosition(10, 135);
    vAxisValue.setPosition(vAxis.getGlobalBounds().width + 20, 135);

    povXAxis.setPosition(10, 160);
    povXAxisValue.setPosition(povXAxis.getGlobalBounds().width + 20, 160);

    povYAxis.setPosition(10, 185);
    povYAxisValue.setPosition(povYAxis.getGlobalBounds().width + 20, 185);

    btn.setPosition(10, 210);
    btnValue.setPosition(btn.getGlobalBounds().width + 20, 210);


    int btnNb = sf::Joystick::getButtonCount(0);

    if(sf::Joystick::isConnected(0))
    {
        std::cout << "Number of buttons : " << btnNb << std::endl;
    }

    while(window.isOpen())
    {

        sf::Event e;
        while(window.pollEvent(e))
        {
            switch(e.type)
            {
                case sf::Event::JoystickButtonPressed :
                {
                    std::string s;
                    for(int i = 0; i < btnNb; i++)
                    {
                        if (sf::Joystick::isButtonPressed(0, i))
                        {
                            std::stringstream ss;
                            ss << i;
                            s += ss.str() + " ";
                        }
                    }

                    btnValue.setString(s);

                    break;
                }

                case sf::Event::JoystickMoved:
                {
                    std::stringstream ss, ss2, ss3, ss4, ss5, ss6, ss7, ss8, ss9;
                    ss << sf::Joystick::getAxisPosition(0, sf::Joystick::X);
                    xAxisValue.setString(ss.str());
                    ss2 << sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
                    yAxisValue.setString(ss2.str());
                    ss3 << sf::Joystick::getAxisPosition(0, sf::Joystick::Z);
                    zAxisValue.setString(ss3.str());
                    ss4 << sf::Joystick::getAxisPosition(0, sf::Joystick::R);
                    rAxisValue.setString(ss4.str());
                    ss5 << sf::Joystick::getAxisPosition(0, sf::Joystick::U);
                    uAxisValue.setString(ss5.str());
                    ss6 << sf::Joystick::getAxisPosition(0, sf::Joystick::V);
                    vAxisValue.setString(ss6.str());
                    ss7 << sf::Joystick::getAxisPosition(0, sf::Joystick::PovX);
                    povXAxisValue.setString(ss7.str());
                    ss8 << sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);
                    povYAxisValue.setString(ss8.str());
                    break;
                }



                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;

            }
        }
        window.clear();
        window.draw(xAxis);
        window.draw(xAxisValue);
        window.draw(yAxis);
        window.draw(yAxisValue);
        window.draw(zAxis);
        window.draw(zAxisValue);
        window.draw(rAxis);
        window.draw(rAxisValue);
        window.draw(uAxis);
        window.draw(uAxisValue);
        window.draw(vAxis);
        window.draw(vAxisValue);
        window.draw(povXAxis);
        window.draw(povXAxisValue);
        window.draw(povYAxis);
        window.draw(povYAxisValue);
        window.draw(btn);
        window.draw(btnValue);
        window.display();
    }

    return 0;
}
