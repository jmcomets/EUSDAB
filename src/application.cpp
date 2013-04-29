#include <application.h>

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
    }

    void Application::update()
    {
    }

    void Application::render()
    {
    }
}
