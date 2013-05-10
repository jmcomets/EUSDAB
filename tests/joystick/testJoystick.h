#ifndef TEST_JOYSTICK_H_
#define TEST_JOYSTICK_H_

#include <vector>
#include <entity.h>
#include <application.h>
#include <state.h>
#include <input/controller.h>
#include <input/mapping.h>
#include "painter.h"

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
            Graphics::Painter _painter;
    };

    class JoystickTestState: public State
    {
        public:
            JoystickTestState(JoystickTestState &&) = default;
            JoystickTestState(const JoystickTestState &) = delete;
            JoystickTestState & operator=(const JoystickTestState &) = delete;

            JoystickTestState();
            ~JoystickTestState();

            void onUp(const Event &);
            void onDown(const Event &);
            void onLeft(const Event &);
            void onRight(const Event &);

            // Action events
            virtual void onA(Event const &);
            virtual void onB(Event const &);
            virtual void onX(Event const &);
            virtual void onY(Event const &);
            virtual void onZ(Event const &);
            virtual void onTrigger(Event const &);


            void onNextFrame();

        private:
            Input::Event::Ratio _x, _y;
            const std::size_t _id;
    };
}

#endif
