#include "testentity.h"
#include <stdexcept>
#include <entityparser.h>
#include <state.h>

namespace EUSDAB
{
    static Input::Mapping * makeMapping()
    {
        return nullptr;
    }

    static Physics::World * makeWorld()
    {
        return nullptr;
    }

    EntityTest::EntityTest(sf::RenderWindow & window):
        Application(window),
        _input(makeMapping()),
        _physics(_input, makeWorld()),
        _graphics(_window),
        _entity(nullptr)
    {
        EntityParser entityParser;
        _entity = entityParser.loadEntity("../../assets/entities/rickhard");
        if (_entity == nullptr)
        {
            throw std::runtime_error("Rick Hard entity wasn't loaded");
        }

        _input.addSpeaker(_entity);
        //_physics.addEntity(_entity);
        //_graphics.addEntity(_entity);
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
