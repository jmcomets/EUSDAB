#include "testentity.h"
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
    }

    static Entity * makeMapEntity(sf::RenderWindow & window)
    {
        EntityParser entityParser;
        Entity * map = entityParser.loadEntity("../../assets/entities/map_demo");
        if (map == nullptr)
        {
            throw std::runtime_error("Map entity wasn't loaded");
        }

        // Shorten halfwidth / halfheight
        typedef unsigned int Size;
        static auto h = [](const Size & v)
        {
            typedef Physics::Unit U;
            return static_cast<U>(v) / static_cast<U>(2);
        };

        // Move map to center
        sf::Vector2<Size> size = window.getSize();
        map->position() = Physics::Vector2(h(size.x), h(size.y));

        // Get texture
        //State * s = map->state();                      assert(s  != nullptr);
        //Animation * a = s->animation();                assert(a  != nullptr);
        //Frame::TexturePtr tx = a->current().texture(); assert(tx != nullptr);

        // Set window size to map size
        //window.setSize(tx->getSize());

        return map;
    }

    Physics::World * makePhysicsWorld()
    {
        using namespace Physics;
        return new World(AABB(0, 0, 800, 600), Vector2(0, 0));
    }

    EntityTest::EntityTest(sf::RenderWindow & window):
        Application(window), _entityList(),
        _graphics(_window)
    {
        // Map
        _entityList.push_back(makeMapEntity(window));

        // Players
        initPlayerEntities(_entityList);

        // Input
        Input::Mapping * mapping = new Input::JoystickMapping(_entityList.begin() + 1, _entityList.end());
        _input = new Input::Controller(_entityList.begin() + 1, _entityList.end(), mapping);

        // Physics
        Physics::World * world = makePhysicsWorld();
        _physics = new Physics::Controller(*_input, world);
        _physics->addEntity(_entityList.begin(), _entityList.end());

        // Graphics
        _graphics.addEntity(_entityList.begin(), _entityList.end());
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
