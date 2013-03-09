#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <SFML/Graphics.hpp>

#include "animation.h"

class Application
{
    public:
        explicit Application();

        virtual ~Application();

        void run();

    protected:
        virtual void event(sf::Event const & e);
        virtual void update();
        virtual void render();

        sf::RenderWindow _window;

        Graphics::Animation _animation;
};

#endif
