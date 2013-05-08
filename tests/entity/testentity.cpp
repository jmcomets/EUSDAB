#include "testentity.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <state.h>

namespace EUSDAB
{
    EntityTest::EntityTest(sf::RenderWindow & window):
        Application(window), _entityParser(), _entity(nullptr)
    {
        _entity = _entityParser.loadEntity("../../assets/entities/rickhard");
        if (_entity == nullptr)
        {
            throw std::runtime_error("Entity wasn't loaded");
        }
        _window.setFramerateLimit(6);
    }

    EntityTest::~EntityTest()
    {
    }

    void EntityTest::event()
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

    void EntityTest::update()
    {
        // TODO: use advance directly on entity
        _entity->state()->animation()->advance(); // Note: already done in State
    }

    void EntityTest::render()
    {
        // TODO: Draw directly the entity ?
        _window.draw(_entity->state()->animation()->sprite()); // Note: Graphics::Controller does this
    }
}
