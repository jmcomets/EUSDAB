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
    }

    EntityTest::~EntityTest()
    {
        delete _entity;
    }

    void EntityTest::update()
    {
        _entity->state()->animation()->advance(); // Note: this is done in State
    }

    void EntityTest::render()
    {
        _window.draw(_entity->state()->animation()->sprite()); // Note: this is in Graphics::Painter
    }
}
