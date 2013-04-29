#ifndef INPUT_STATES_TEST_H_
#define INPUT_STATES_TEST_H_

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

            private:
                Input::Event::Ratio _n;
        };
    }
}

#endif
