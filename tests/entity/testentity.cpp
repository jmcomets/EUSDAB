#include "testentity.h"
#include <list>
#include <stdexcept>
#include <cassert>
#include <entityparser.h>
#include <state.h>
#include <input/joystickmapping.h>
#include <physics/world.h>

namespace EUSDAB
{
    static std::vector<Entity *> makeEntities()
    {
        EntityParser entityParser;

        Entity * e = entityParser.loadEntity("../../assets/entities/rickhard");
        if (e == nullptr)
        {
            throw std::runtime_error("Rick Hard entity wasn't loaded");
        }
        std::vector<Entity *> cont;
        cont.push_back(e);

        // Add extra (mock) entities
        typedef std::vector<Entity *>::size_type Size;
        constexpr Size nbMockEntities = 4;
        static Movement mockMvt(Movement::Noop, Movement::None);
        for (Size i = 0; i < nbMockEntities - 1; i++)
        {
            Entity * e = new Entity();
            e->addState(new State(mockMvt));
            e->setState(mockMvt);
            cont.push_back(e);
        };

        return cont;
    }

    Physics::World * makePhysicsWorld()
    {
        using namespace Physics;
        return new World(AABB(0, 0, 800, 600), Vector2(0, 0));
    }

    EntityTest::EntityTest(sf::RenderWindow & window):
        Application(window), _entityList(makeEntities()),
        _graphics(_window)
    {
        // Graphics
        _graphics.addEntity(_entityList.begin(), _entityList.end());

        // Input
        Input::Mapping * mapping = new Input::JoystickMapping(_entityList.begin(), _entityList.end());
        _input = new Input::Controller(_entityList.begin(), _entityList.end(), mapping);

        // Physics
        Physics::World * world = makePhysicsWorld();
        _physics = new Physics::Controller(*_input, world);
    }

    EntityTest::~EntityTest()
    {
        delete _input;
        delete _physics;
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
                _input->pushEvent(e);
            }
        }
        _input->nextFrame();
    }

    void EntityTest::update()
    {
        _physics->update();
        _input->update();
    }

    void EntityTest::render()
    {
        _graphics.draw();
    }
}
