#include <application.h>

Application::Application(): 
    _window(sf::VideoMode(800, 600), "EUSDAB"), _tm(),
    _animation(*_tm.get("./data/tileset.ts"))
{
}

Application::~Application()
{
}

void Application::run()
{
    while (_window.isOpen())
    {
        sf::Event e;
        while(_window.pollEvent(e))
        {
            event(e);
        }
        update();
        _window.clear();
        render();
        _window.display();
    }
}

void Application::event(sf::Event const & e)
{
    if (e.type == sf::Event::Closed)
    {
        _window.close();
    }
}

void Application::update()
{
    _animation.nextFrame();
}

void Application::render()
{
    _animation.render(_window);
}

