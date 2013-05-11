#ifndef TEST_JOYSTICK_H_
#define TEST_JOYSTICK_H_

#include <vector>
#include <entity.h>
#include <application.h>
#include <state.h>
#include <input/controller.h>
#include <input/mapping.h>
#include <view/controller.h>

namespace EUSDAB
{
    class JoystickTest: public Application
    {
        public:
            JoystickTest() = delete;
            JoystickTest(JoystickTest &&) = delete;
            JoystickTest(const JoystickTest &) = delete;
            JoystickTest & operator=(const JoystickTest &) = delete;

            JoystickTest(sf::RenderWindow &);
            ~JoystickTest();

        protected:
            void update();
            void event();
            void render();

        private:
            // Player
            std::vector<Entity *> _playerList;

            // Controller
            Input::Controller * _input;
            Input::Mapping * _mapping;

            //Graphic::Controller
            Graphics::Controller _painter;
    };
}

#endif
