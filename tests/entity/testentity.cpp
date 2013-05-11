#include "testentity.h"
#include <stdexcept>
#include <iostream>
#include <entityparser.h>
#include <state.h>

namespace EUSDAB
{
    EntityTest::EntityTest(sf::RenderWindow & window):
        Application(window),
        _entity(nullptr)
    {
        EntityParser entityParser;
        _entity = entityParser.loadEntity("../../assets/entities/rickhard");
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
    }

    void EntityTest::render()
    {
    }
}
