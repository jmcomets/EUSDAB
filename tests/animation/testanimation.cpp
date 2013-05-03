#include "testanimation.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <texturemanager.h>

namespace EUSDAB
{
    AnimationTest::AnimationTest(sf::RenderWindow & window):
        Application(window), _animParser(), _animation(nullptr)
    {
        _animation = _animParser.loadAnimation("nyan_cat");
        if (_animation == nullptr)
        {
            throw std::runtime_error("Animation wasn't loaded");
        }
        // ~1 images per second
        _window.setFramerateLimit(20);
        _animation->setFPI(20);
    }

    AnimationTest::~AnimationTest()
    {
    }

    void AnimationTest::event()
    {
        sf::Event e;
        while (_window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                _window.close();
            }
            else if (e.type == sf::Event::KeyPressed)
            {
                if (e.key.code == sf::Keyboard::Space)
                {
                    bool p(1 - _animation->paused());
                    if (p == false)
                    {
                        std::cout << "Unpausing";
                    }
                    else
                    {
                        std::cout << "Pausing";
                    }
                    std::cout << " animation" << std::endl;
                    _animation->setPaused(p);
                }
            }
        }
    }

    void AnimationTest::update()
    {
        _animation->advance();
    }

    void AnimationTest::render()
    {
        _window.draw(_animation->sprite());
    }
}
