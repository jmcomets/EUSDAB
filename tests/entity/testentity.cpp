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
        return new Physics::World(0, 0, 800, 600); // FIXME
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
        _graphics.addEntity(_entity);
        //_physics.addEntity(_entity);
    }

    EntityTest::~EntityTest()
    {
        delete _entity;
    }

    void EntityTest::event()
    {
        sf::Event e;
        std::vector<sf::Event> eventList;
        while (_window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                _window.close();
            }
            else if (e.type == sf::Event::KeyPressed)
            {
                eventList.push_back(e);
            }
            else if (e.type == sf::Event::KeyReleased)
            {
                eventList.push_back(e);
            }
            else if(e.type == sf::Event::JoystickButtonPressed
                    || e.type == sf::Event::JoystickMoved)
            {
                eventList.push_back(e);
            }
        }
        _input.pushEvent(eventList.begin(), eventList.end());
        _input.nextFrame();
    }

    void EntityTest::update()
    {
        _physics.update();
        _input.update();
    }

    void EntityTest::render()
    {
        _graphics.draw();
    }
}
