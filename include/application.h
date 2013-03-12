#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <graphics.h>
#include <animation.h>

class Application
{
    public:
        Application();
        virtual ~Application();
        void run();

    protected:
        virtual void event(sf::Event const & e);
        virtual void update();
        virtual void render();

    private:
        sf::RenderWindow _window;
        Graphics::Animation _animation;
};

#endif
