#ifndef MY_APPLICATION_H_
#define MY_APPLICATION_H_

#include <vector>
#include <application.h>
#include <input/controller.h>
#include <physics/controller.h>
#include <graphics/controller.h>
#include <entity.h>
#include <SFML/Audio.hpp>

namespace EUSDAB
{
    class MyApplication: public Application
    {
        public:
            MyApplication() = delete;
            MyApplication(MyApplication &&) = delete;
            MyApplication(const MyApplication &) = delete;
            MyApplication & operator=(const MyApplication &) = delete;

            MyApplication(sf::RenderWindow & window,
                    std::string const & map_name,
                    std::string const & player1,
                    std::string const & player2,
                    std::string const & player3,
                    std::string const & player4,
                    bool);
            ~MyApplication();

            typedef std::vector<Entity *> EntityList;

        protected:
            void update();
            void render();
            void event();

        private:
            void loadPlayer(std::string const &, unsigned int);
            void loadMap(std::string const &);

            // List of entities to control
            MyApplication::EntityList _entityList;
            MyApplication::EntityList _players;

            // Input
            Input::Controller * _input;

            // Physics
            Physics::Controller * _physics;

            // Graphics
            Graphics::Controller * _graphics;

            sf::Music _music;
    };
}

#endif
