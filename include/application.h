#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <SFML/Graphics/RenderWindow.hpp>

namespace EUSDAB
{
    // Abstract class providing basic setup for our application,
    // the 3 methods `event()`, `update()` and `render()`
    // should be overriden in a derived class to do the
    // corresponding game logic (game loop is the `run()` method).
    class Application
    {
        public:
            Application() = delete;
            Application(Application &&) = delete;
            Application(const Application &) = delete;
            Application & operator=(const Application &) = delete;

            Application(sf::RenderWindow &);
            virtual ~Application();

            // Game loop
            void run();

        protected:
            // 3-step game loop callbacks
            virtual void event();
            virtual void update();
            virtual void render();

            // SFML context
            sf::RenderWindow & _window;
    }; 
}

#endif
