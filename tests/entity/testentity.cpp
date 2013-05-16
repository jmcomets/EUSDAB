#include "testentity.h"
#include <iostream>
#include <sstream>
#include <list>
#include <stdexcept>
#include <cassert>
#include <entityparser.h>
#include <state.h>
#include <input/joystickmapping.h>
#include <physics/world.h>
#include <SFML/Window/Joystick.hpp>

namespace EUSDAB
{
    template <typename Container>
        static void initPlayerEntities(Container & cont)
    {
        EntityParser entityParser;

        // Type returned by sf::Joystick::
        typedef unsigned int Size;

        for (Size i = 0; sf::Joystick::isConnected(i); i++)
        {
            Entity * e = entityParser.loadEntity("../../assets/entities/rickhard");
            if (e == nullptr)
            {
                throw std::runtime_error("Rick Hard entity wasn't loaded");
            }
            cont.push_back(e);
        }

        if (cont.empty())
        {
            throw std::runtime_error("No joysticks detected");
        }
    }

    static Entity * makeMapEntity(sf::RenderWindow & window)
    {
        EntityParser entityParser;
        Entity * map = entityParser.loadEntity("../../assets/entities/map_bazar");
        if (map == nullptr)
        {
            throw std::runtime_error("Map entity wasn't loaded");
        }

        // Shorten halfwidth / halfheight
        typedef unsigned int Size;
        static auto h = [](const Size & v)
        {
            return static_cast<Physics::Unit>(v) 
                / static_cast<Physics::Unit>(2);
        };

        // Move map to center of window to start with
        sf::Vector2<Size> size = window.getSize();
        map->position() = Physics::Vector2(h(size.x), h(size.y));

        // Map is not gravitable
        map->gravitable() = false;

        return map;
    }

    Physics::World * makePhysicsWorld()
    {
        using namespace Physics;
        return new World(AABB(0, 0, 600, 480), Vector2(0, 0.01));
    }

    EntityTest::EntityTest(sf::RenderWindow & window):
        Application(window), _entityList()
    {
        // Map
        _entityList.push_back(makeMapEntity(window));

        // Players
        initPlayerEntities(_entityList);

        // Input
        _input = new Input::Controller(_entityList.begin() + 1, _entityList.end(), 
                new Input::JoystickMapping(_entityList.begin() + 1, _entityList.end()));

        // Physics
        Physics::World * world = makePhysicsWorld();
        _physics = new Physics::Controller(*_input, world);
        _physics->addEntity(_entityList.begin(), _entityList.end());

        // Graphics
        _graphics = new Graphics::Controller(_window);
        _graphics->addEntity(_entityList.begin(), _entityList.end());
    }

    EntityTest::~EntityTest()
    {
        delete _input;
        delete _physics;
        delete _graphics;
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
        _graphics->draw();
    }
}
