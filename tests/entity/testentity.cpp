#include "testentity.h"
#include <list>
#include <stdexcept>
#include <entityparser.h>
#include <state.h>
#include <input/keyboardmapping.h>
#include <physics/world.h>

namespace EUSDAB
{
    static Input::Mapping * makeMapping(Entity * e)
    {
        std::list<Entity *> mockPlayerList{e};
        return new Input::KeyboardMapping(mockPlayerList.begin(), mockPlayerList.end());
    }

    static Physics::World * makeWorld()
    {
        return new Physics::World(0, 0, 800, 600);
    }

    EntityTest::EntityTest(sf::RenderWindow & window):
        Application(window),
        _input(makeMapping(_entity)),
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
