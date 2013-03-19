#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <array>
#include <vector>
#include <SFML/Graphics.hpp>
#include <entity.h>
#include <input/controller.h>
#include <config.h>

namespace EUSDAB
{
    class Application
    {
        public:
            Application(sf::RenderWindow *);
            Application() = delete;
            Application(Application &&) = delete;
            Application(const Application &) = delete;
            ~Application();
            Application & operator=(const Application &) = delete;
            void run();

        protected:
            virtual void event();
            virtual void update();
            virtual void render();

        private:
            // SFML context
            sf::RenderWindow * _window;

            // World
            std::array<Entity *, Config::NbPlayers> _playerList;
            std::vector<Entity *> _entityList;

            // Controller
            Input::Controller * _input;
    };
}

#endif
