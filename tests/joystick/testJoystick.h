#ifndef TEST_JOYSTICK_H_
#define TEST_JOYSTICK_H_

#include <application.h>

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

    };
}

#endif
