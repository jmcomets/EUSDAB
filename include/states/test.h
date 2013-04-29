#ifndef INPUT_STATES_TEST_H_
#define INPUT_STATES_TEST_H_

#include <cstddef>
#include <state.h>

namespace EUSDAB
{
    namespace States
    {
        class Test: public State
        {
            public:
                Test(Test &&) = default;
                Test(const Test &) = delete;
                Test & operator=(const Test &) = delete;

                Test();
                virtual ~Test();

                virtual void onUp(const Event &);
                virtual void onDown(const Event &);
                virtual void onLeft(const Event &);
                virtual void onRight(const Event &);

                virtual void onNextFrame();

            private:
                Input::Event::Ratio _x, _y;
                const std::size_t _id;
        };
    }
}

#endif
