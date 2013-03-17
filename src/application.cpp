#include <application.h>

#include <entity.h>
#include <input/controller.h>

namespace EUSDAB
{
    Application::Application(sf::RenderWindow * window):
        _window(window),
        _playerList(),
        _entityList(),
        _input(nullptr)
    {
        // Generation of player
        _playerList.fill(nullptr);
        _playerList[0] = new Entity();
        _playerList[1] = new Entity();

        // Generation of world
        _entityList.emplace_back(new Entity());

        // Controller creation
        _input = new Input::Controller(_playerList);

        // Controllers filling
        for(auto e : _entityList)
            _input->addEntity(e);
    }

    Application::~Application()
    {
        // Controller delete
        if(_input != nullptr)
            delete _input;

        // Entities delete
        for(auto e : _playerList)
            delete e;

        for(auto e : _entityList)
            delete e;
    }

    void Application::run()
    {
        while (_window->isOpen())
        {
            event();
            update();
            _window->clear();
            render();
            _window->display();
        }
    }

    void Application::event()
    {
        sf::Event e;
        std::vector<sf::Event> eventList;
        while(_window->pollEvent(e))
        {
            if(e.type == sf::Event::Closed)
            {
                _window->close();
            }

            if(e.type == sf::Event::KeyPressed)
            {
                eventList.push_back(e);
            }

            if(e.type == sf::Event::KeyReleased)
            {
                eventList.push_back(e);
            }
        }

        _input->pushEvent(eventList);
    }

    void Application::update()
    {
        // Controllers update
        _input->update();
    }

    void Application::render()
    {
    }
}

