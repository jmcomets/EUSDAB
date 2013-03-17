#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <array>
#include <vector>

#include <SFML/Graphics.hpp>

#include <config.h>

namespace EUSDAB
{
    class Entity;

    namespace Input
    {
        class Controller;
    }

    class Application
    {
        public:
            Application(sf::RenderWindow *);
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
            std::array<Entity *, Config::NbPlayers> _playerList;
            std::vector<Entity *> _entityList;

            // Controller
            Input::Controller * _input;
    };
}

#endif

