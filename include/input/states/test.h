#ifndef INPUT_STATES_TEST_H_
#define INPUT_STATES_TEST_H_

#include <input/state.h>

namespace EUSDAB
{
    namespace Input
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

                    virtual void onUp(Event const &);
                    virtual void onDown(Event const &);
                    virtual void onLeft(Event const &);
                    virtual void onRight(Event const &);

                protected:
                    double _n;
            };
        }
    }
}

#endif

