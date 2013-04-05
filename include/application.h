#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <vector>

#include <SFML/Graphics.hpp>

#include <entity.h>
#include <input/controller.h>

namespace EUSDAB
{
    class Application
    {
        public:
            Application(sf::RenderWindow *);
            Application() = delete;
            Application(Application &&) = delete;
            Application(const Application &) = delete;
            Application & operator=(const Application &) = delete;

            virtual ~Application();

            void run();

        protected:
            virtual void event();
            virtual void update();
            virtual void render();

        private:
            // SFML context
            sf::RenderWindow * _window;

            // World
            std::vector<Entity *> _playerList;
            std::vector<Entity *> _entityList;

            // Controller
            Input::Controller * _input;
    };
}

#endif
