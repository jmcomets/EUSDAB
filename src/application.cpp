#include <application.h>
#include <SFML/Window/Event.hpp>

#include <iostream>

namespace EUSDAB
{
    Application::Application(sf::RenderWindow & window):
        _window(window)
    {
        // Window's config
        _window.setKeyRepeatEnabled(false);
        _window.setMouseCursorVisible(false);
        _window.setFramerateLimit(60);
        _window.setTitle("EUSDAB");
        _window.setVerticalSyncEnabled(true);

        sf::Image icon;
        if(icon.loadFromFile("../../assets/icon.png"))
        {
            _window.setIcon(32, 32, icon.getPixelsPtr());
        }
        else
        {
            std::cout << "FFAIIIILLLL" << std::endl;
        }
    }

    Application::~Application()
    {
    }

    void Application::run()
    {
        while (_window.isOpen())
        {
            event();
            update();
            _window.clear();
            render();
            _window.display();
        }
    }

    void Application::event()
    {
        sf::Event e;
        while (_window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                _window.close();
            }
        }
    }

    void Application::update()
    {
    }

    void Application::render()
    {
    }
}
