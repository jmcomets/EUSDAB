#include "testanimation.h"
#include <string>
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <textureManager.h>

namespace EUSDAB
{
    namespace Priv
    {
        static void loadNyanAnimation(Animation & animation)
        {
            auto addAnimationFrame = [](Animation & animation,
                    const std::string & filename) {
                using namespace Graphics;
                typedef TextureManager::TexturePtr TexturePtr;
                TexturePtr tx = TextureManager::loadTexture(filename);
                animation.addFrame(Frame(tx));
            };
            addAnimationFrame(animation, "nyan_cat/frame1.png");
            addAnimationFrame(animation, "nyan_cat/frame2.png");
            addAnimationFrame(animation, "nyan_cat/frame3.png");
            addAnimationFrame(animation, "nyan_cat/frame4.png");
        }
    }

    AnimationTest::AnimationTest(sf::RenderWindow & window):
        Application(window), _animation()
    {
        Priv::loadNyanAnimation(_animation);
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
                    bool p(1 - _animation.paused());
                    if (p == false)
                    {
                        std::cout << "Unpausing";
                    }
                    else
                    {
                        std::cout << "Pausing";
                    }
                    std::cout << " animation" << std::endl;
                    _animation.setPaused(p);
                }
            }
        }
    }

    void AnimationTest::update()
    {
        _animation.advance();
    }

    void AnimationTest::render()
    {
        _window.draw(_animation.sprite());
    }
}
