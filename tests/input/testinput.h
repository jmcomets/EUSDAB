#ifndef TEST_INPUT_H_
#define TEST_INPUT_H_

#include <vector>
#include <entity.h>
#include <application.h>
#include <state.h>
#include <input/controller.h>

namespace EUSDAB
{
    class InputTest: public Application
    {
        public:
            InputTest() = delete;
            InputTest(InputTest &&) = delete;
            InputTest(const InputTest &) = delete;
            InputTest & operator=(const InputTest &) = delete;

            InputTest(sf::RenderWindow &);
            ~InputTest();

        protected:
            void event();
            void update();

        private:
            // World
            std::vector<Entity *> _playerList;

            // Controller
            Input::Controller * _input;
    };

    class InputTestState: public State
    {
        public:
            InputTestState(InputTestState &&) = default;
            InputTestState(const InputTestState &) = delete;
            InputTestState & operator=(const InputTestState &) = delete;

            InputTestState();
            ~InputTestState();

            void onUp(const Event &);
            void onDown(const Event &);
            void onLeft(const Event &);
            void onRight(const Event &);

            void onNextFrame();

        private:
            Input::Event::Ratio _x, _y;
            const std::size_t _id;
    };
}

#endif
