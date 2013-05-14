#include "teststates.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <state.h>

namespace EUSDAB
{
    StatesTest::StatesTest(sf::RenderWindow & window):
        Application(window), _entityParser(), _entity(nullptr)
    {
        _entity = _entityParser.loadEntity("../../assets/entities/rickhard");
        if (_entity == nullptr)
        {
            throw std::runtime_error("Entity wasn't loaded");
        }
        _window.setFramerateLimit(6);
    }

    StatesTest::~StatesTest()
    {
    }

    void StatesTest::event()
    {
        sf::Event e;
        while (_window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                _window.close();
            }
        }
    }

    void StatesTest::update()
    {
        // TODO: use advance directly on entity
        _entity->state()->animation()->advance();
    }

    void StatesTest::render()
    {
        // TODO: Draw directly the entity ?
        _window.draw(_entity->state()->animation()->sprite());
    }
}
