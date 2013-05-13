#include "testentity.h"
#include <list>
#include <stdexcept>
#include <entityparser.h>
#include <state.h>
#include <input/joystickmapping.h>
#include <physics/world.h>

namespace EUSDAB
{
    template <typename Container>
        static void initEntities(Container & cont)
    {
        EntityParser entityParser;

        Entity * e = entityParser.loadEntity("../../assets/entities/rickhard");
        if (e == nullptr)
        {
            throw std::runtime_error("Rick Hard entity wasn't loaded");
        }
        cont.push_back(e);

        // Add extra (mock) entities
        static auto makeMockEntity = []
        {
            Entity * e = nullptr;
            e->addState(new State(Movement::None));
            e->setState(Movement::Noop);
            return e;
        };
        cont.push_back(makeMockEntity());
        cont.push_back(makeMockEntity());
        cont.push_back(makeMockEntity());
    }

    EntityTest::EntityTest(sf::RenderWindow & window):
        Application(window), _entityList(),
        _input(new Input::JoystickMapping(_entityList.begin(), _entityList.end())),
        _physics(_input, new Physics::World(0, 0, 800, 600)),
        _graphics(_window)
    {
        initEntities(_entityList);
        _input.addSpeaker(_entityList.begin(), _entityList.end());
        _graphics.addEntity(_entityList.begin(), _entityList.end());
        //_physics.addEntity(_entityList.begin(), _entityList.end());
    }

    EntityTest::~EntityTest()
    {
        for (Entity * e : _entityList)
        {
            delete e;
        }
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
            else
            {
                _input.pushEvent(e);
            }
        }
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
