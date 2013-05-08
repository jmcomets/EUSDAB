#include "testPainter.h"

#include <stdexcept>
#include <string>
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <texturemanager.h>
#include <movement.h>
#include <state.h>


namespace EUSDAB
{
    Entity * entity;
    PainterTest::PainterTest(sf::RenderWindow & window):
        Application(window), _entityParser(), _painter(window)
    {
        entity = _entityParser.loadEntity("../../assets/entities/rickhard");
        entity->state()->animation()->setFPI(1);
        entity->state(Movement(Movement::Action::Attack));
        if (entity == nullptr)
        {
            throw std::runtime_error("Animation wasn't loaded");
        }
        _painter.addEntity(entity);
        _window.setFramerateLimit(30);
        _window.setVerticalSyncEnabled(true);
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
                    _painter.removeEntity(entity);
                }
            }
        }
    }

    void PainterTest::update()
    {
    }

    void PainterTest::render()
    {
        _painter.draw();
    }
}
