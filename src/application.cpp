#include <application.h>
#include <SFML/Window/Event.hpp>

#include <iostream>

namespace EUSDAB {

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
    _window.clear(sf::Color::Black);
    while (_window.isOpen())
    {
        sf::Event e;
        while (_window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                _window.close();
            }
            else if(e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
            {
                _window.close();
            }
            else
            {
                handleEvent(e);
            }
        }

        update();

        _window.clear();
        renderTo(_window);
        _window.display();
    }
}

void Application::handleEvent(const sf::Event&)
{
}

void Application::update()
{
}

void Application::renderTo(sf::RenderTarget&)
{
}

} // namespace EUSDAB
