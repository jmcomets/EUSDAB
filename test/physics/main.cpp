#include <iostream>
#include <cmath>

#include "vector2.h"
#include "obb2.h"

#include <SFML/Graphics.hpp>

#define PAS_TRANSLATION 1.0
#define PAS_ROTATION M_PI / 16.

using namespace EUSDAB;

template <typename T>
void draw(Physics::Vector2<T> const & v)
{
    std::cout << "v : (" << v.x() << ", " << v.y() << ")" << std::endl;
}


int main()
{
    Physics::Vector2<int> v(1, 2);
    draw<int>(v);
    draw<int>(v * 2);
    draw<int>(v + Physics::Vector2<int>(-1, -2));
    draw<int>(v / 2);

    Physics::Vector2<float> vf(3.0, 4.0);

    draw<float>(vf);
    draw<float>(vf.norm());
    draw<float>(vf.translate(Physics::Vector2<float>(1.5, -5.25)));
    draw<float>(vf.translate(Physics::Vector2<int>(-1, 5)));
    vf.x(0);
    vf.y(1);
    draw<float>(vf);
    draw<float>(vf.rotate(M_PI/2));

    //v + vf;

    std::cout << std::endl;
    draw<int>(v);
    draw<float>(vf);
    draw<float>(vf - vf / 2);

    Physics::OBB2<float> obb(100, 60, Physics::Vector2<float>(200, 200), -0*M_PI/3);
    Physics::OBB2<float> obb2(100, 60, Physics::Vector2<float>(200, 200), 0*M_PI/4);
    obb.color = sf::Color::Blue;
    //Physics::OBB2<float> obb3(100, 60, Physics::Vector2<float>(200, 200), -2*M_PI/3);
    //Physics::OBB2<float> obb4(100, 60, Physics::Vector2<float>(200, 200), -M_PI);

    std::cout << "Obb1 : X = (" << obb.X().x() << ", " << obb.X().y() <<  ")" << std::endl;
    std::cout << "Obb1 : Y = (" << obb.Y().x() << ", " << obb.Y().y() <<  ")" << std::endl;

    std::cout << "Obb2 : X = (" << obb2.X().x() << ", " << obb2.X().y() <<  ")" << std::endl;
    std::cout << "Obb2 : Y = (" << obb2.Y().x() << ", " << obb2.Y().y() <<  ")" << std::endl;
    std::cout << "Obb1 : angle = (" << obb.angle() << ")" << std::endl;
    std::cout << "Obb2 : angle = (" << obb2.angle() << ")" << std::endl;
    std::cout << "Intersect : " << (obb.collides(obb2) ? "true" : "false") << std::endl;

    //sf::RectangleShape r(sf::Vector2<float>(10, 20));
    //r.setOutlineColor(sf::Color::Red);

    sf::RenderWindow _window(sf::VideoMode(800, 600), "EUSDAB");
    while(_window.isOpen())
    {
        sf::Event e;
        while(_window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed)
            {
                _window.close();
            }
            if (e.type == sf::Event::KeyPressed)
            {
                switch(e.key.code)
                {
                    case sf::Keyboard::Up:
                        obb.translate(0.0, -PAS_TRANSLATION);
                        break;

                    case sf::Keyboard::Down:
                        obb.translate(0.0,PAS_TRANSLATION);
                        break;

                    case sf::Keyboard::Left:
                        obb.translate(-PAS_TRANSLATION,0.0);
                        break;

                    case sf::Keyboard::Right:
                        obb.translate(PAS_TRANSLATION,0.0);
                        break;

                    case sf::Keyboard::A:
                        obb.rotate(PAS_ROTATION);
                        break;

                    case sf::Keyboard::Z:
                        obb.rotate(-PAS_ROTATION);
                        break;

                    default:
                        break;
                }
                std::cout << "(x, y) : (" << obb.center().x() << ", " << obb.center().y() << ")";
                std::cout << " | (" << obb2.center().x() << ", " << obb2.center().y() << ")" << std::endl;
                std::cout << "Obb1 : X = (" << obb.X().x() << ", " << obb.X().y() <<  ")" << std::endl;
                std::cout << "Obb1 : Y = (" << obb.Y().x() << ", " << obb.Y().y() <<  ")" << std::endl;
                std::cout << "Obb1 : angle = (" << obb.angle() << ")" << std::endl;
                std::cout << "Obb2 : angle = (" << obb2.angle() << ")" << std::endl;
                std::cout << "Intersect : " << (obb.collides(obb2) ? "true" : "false") << std::endl;

                if (obb.collides(obb2))
                {
                    obb.color = sf::Color::Red;
                }
                else
                {
                    obb.color = sf::Color::Green;
                }
            }
        }

        _window.clear(sf::Color::White);
        //_window.draw(r);
        obb.render(_window);
        obb2.render(_window);
        //obb3.render(_window);
        //obb4.render(_window);
        _window.display();
    }
    return 0;
}

