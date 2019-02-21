#include "my_application.h"
#include <string>
#include <stdexcept>
#include <entityparser.h>
#include <state.h>
#include <input/joystickmapping.h>
#include <physics/world.h>
#include <percentageLife.h>
#include <infiniteLife.h>
#include <iostream>
#include <cassert>
#include <thread>

static std::string const ROOT_DIR = "../../";

namespace EUSDAB
{
    MyApplication::MyApplication(sf::RenderWindow & window,
            std::string const & map_name,
            std::string const & player1,
            std::string const & player2,
            std::string const & player3,
            std::string const & player4,
            bool psyche):
        Application(window), _entityList(), _music()
    {
        std::cout << "Map: " << map_name << std::endl;

        std::cout << "Player 1:" << player1 << std::endl;
        std::cout << "Player 2:" << player2 << std::endl;
        std::cout << "Player 3:" << player3 << std::endl;
        std::cout << "Player 4:" << player4 << std::endl;

        std::cout << ">> Loading map..." << std::endl;

        // Map
        loadMap(map_name);

        std::vector<std::thread> loaderThreads;

        // // Players
        if(player1 != "none")
            loaderThreads.push_back(std::thread([this, &player1]() { this->loadPlayer(player1, 0); }));
        if(player2 != "none")
            loaderThreads.push_back(std::thread([this, &player2]() { this->loadPlayer(player2, 1); }));
        if(player3 != "none")
            loaderThreads.push_back(std::thread([this, &player3]() { this->loadPlayer(player3, 2); }));
        if(player4 != "none")
            loaderThreads.push_back(std::thread([this, &player4]() { this->loadPlayer(player4, 3); }));

        for(auto & t : loaderThreads)
        {
            t.join();
        }

        // Input
        Input::Mapping * mapping = new Input::JoystickMapping(_players.begin(), _players.end());
        _input = new Input::Controller(_entityList.begin(), _entityList.end(), mapping);

        // Physics
        using namespace Physics;
        Unit w, h, x, y;
        if(map_name == "map_bazar")
        {
            x = 700;
            y = 200;
            w = 2300;
            h = 1200;
        }
        else if (map_name == "map_bar")
        {
            x = 700;
            y = 250;
            w = 2500;
            h = 1500;
        }
        else
        {
            throw std::runtime_error("Wrong map name");
        }

        World * world = new World(AABB(x, y, w, h), Vector2(0, 0.35f));
        _physics = new Controller(*_input, world);
        _physics->addEntity(_entityList.begin(), _entityList.end());
        _physics->addPlayer(_players.begin(), _players.end());

        // Graphics
        EntityList::iterator playersBegin = _entityList.begin() + (_entityList.size() - _players.size());

        _graphics = new Graphics::Controller(_window,
                playersBegin, _entityList.end(), world, psyche, ROOT_DIR);

        _graphics->addEntity(_entityList.begin(), playersBegin);

        if(psyche == false)
        {
            if (!_music.openFromFile(ROOT_DIR + "assets/audio/musics/bazar.ogg"))
                throw std::runtime_error("Map's music wasn't loaded");
        }
        else
        {
            if (!_music.openFromFile(ROOT_DIR + "assets/audio/musics/harlem.ogg"))
                throw std::runtime_error("Map's music wasn't loaded");
        }
        _music.setLoop(true);
        _music.setVolume(50);
        _music.play();
    }

    MyApplication::~MyApplication()
    {
        delete _input;
        delete _physics;
        delete _graphics;
        for (Entity * e : _entityList)
        {
            delete e;
        }
    }

    void MyApplication::loadPlayer(std::string const & name, unsigned int id)
    {
        static EntityParser entityParser(ROOT_DIR + "assets/entities");

        Entity * e = entityParser.loadEntity(name, false);

        if (e == nullptr)
            throw std::runtime_error(name + " entity wasn't loaded");

        typedef unsigned int Size;
        static auto const h = [](const Size & v)
        {
            return static_cast<Physics::Unit>(v)
                / static_cast<Physics::Unit>(2);
        };

        e->position() = Physics::Vector2(h(500 + id * 500), h(0));
        e->setInitialPosition(e->position());
        e->setName(e->name());
        e->setLife(new PercentageLife(0, 999));

        _entityList.push_back(e);
        _players.push_back(e);
    }

    void MyApplication::loadMap(std::string const & name)
    {
        EntityParser entityParser(ROOT_DIR + "assets/entities");

        Entity * map = entityParser.loadEntity(name, true);
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
        sf::Vector2<Size> size = _window.getSize();
        map->position() = Physics::Vector2(h(size.x), h(size.y));

        // Map is not gravitable
        map->gravitable() = false;

        //Map life
        map->setLife(new InfiniteLife());

        _entityList.push_back(map);
    }

    void MyApplication::event()
    {
        sf::Event e;
        _window.clear(sf::Color::Black);
        while (_window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                _window.close();
            }
            else if(e.type == sf::Event::KeyPressed)
            {
                if(e.key.code == sf::Keyboard::Escape)
                    _window.close();
            }
            else
            {
                _input->pushEvent(e);
            }
        }
        _input->nextFrame();
    }

    void MyApplication::update()
    {
        _physics->update();
        _input->update();
    }

    void MyApplication::render()
    {
        _graphics->draw();
    }
}

