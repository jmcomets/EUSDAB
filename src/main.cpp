#include <iostream>
#include <cmath>

#define SFML_TEST

#include <physics/hitbox.h>
#include <physics/aabb.h>
#include <physics/vector2.h>

#include <SFML/Graphics.hpp>

#define PAS_TRANSLATION 2.0

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
    draw<float>(vf.translate(Physics::Vector2<float>(1.5, -5.25)));
    draw<float>(vf.translate(Physics::Vector2<int>(-1, 5)));
    vf.x(0);
    vf.y(1);
    draw<float>(vf);

    std::cout << std::endl;
    draw<int>(v);
    draw<float>(vf);
    draw<float>(vf - vf / 2.f);

    Physics::Hitbox<int> hitbox1;
    hitbox1.addAABB(Physics::AABB<int>(10, 0, 10, 10));
    hitbox1.addAABB(Physics::AABB<int>(0, 10, 30, 70));
    hitbox1.addAABB(Physics::AABB<int>(30, 20, 40, 10));
    hitbox1.addAABB(Physics::AABB<int>(0, 80, 10, 30));
    hitbox1.addAABB(Physics::AABB<int>(20, 80, 10, 35));

    Physics::Hitbox<int> hitbox2;
    hitbox2.addAABB(Physics::AABB<int>(100, 130, 200, 200));
    hitbox2.addAABB(Physics::AABB<int>(300, 130, 200, 50));

    hitbox1.setColor(sf::Color::Green);
    hitbox2.setColor(sf::Color::Green);

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
                if(e.key.code == sf::Keyboard::Up)
                    hitbox1.translate(0, -PAS_TRANSLATION);

                if(e.key.code == sf::Keyboard::Down)
                    hitbox1.translate(0, PAS_TRANSLATION);

                if(e.key.code == sf::Keyboard::Left)
                    hitbox1.translate(-PAS_TRANSLATION, 0);

                if(e.key.code == sf::Keyboard::Right)
                    hitbox1.translate(PAS_TRANSLATION, 0);

                if (hitbox1.collide(hitbox2))
                {
                    hitbox1.setColor(sf::Color::Red);
                }
                else
                {
                    hitbox1.setColor(sf::Color::Blue);
                }
            }
        }

        _window.clear(sf::Color::Yellow);
        _window.draw(hitbox1);
        _window.draw(hitbox2);
        _window.display();
    }
    return 0;
}

