#include "testPainter.h"

#include <stdexcept>
#include <string>
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <texturemanager.h>


namespace EUSDAB
{
    PainterTest::PainterTest(sf::RenderWindow & window):
        Application(window), _entityParser(), _painter(window)
    {
        Entity * entity = _entityParser.loadEntity("../../asset/entities/Rickhard");
        if (entity == nullptr)
        {
            throw std::runtime_error("Animation wasn't loaded");
        }
        _painter.addEntity(entity);
        // ~1 images per second
        _window.setFramerateLimit(20);
        //_animation->setFPI(20);
    }

    PainterTest::~PainterTest()
    {
    }

    void PainterTest::event()
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
                    //bool p(1 - _animation->paused());
                    //if (p == false)
                    //{
                        //std::cout << "Unpausing";
                    //}
                    //else
                    //{
                        //std::cout << "Pausing";
                    //}
                    //std::cout << " animation" << std::endl;
                    //_animation->setPaused(p);
                }
            }
        }
    }

    void PainterTest::update()
    {
        //_animation->advance();
        //_painter.update();
    }

    void PainterTest::render()
    {
        _painter.draw();
    }
}
