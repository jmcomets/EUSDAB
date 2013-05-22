#ifndef STATES_WAIT_H_
#define STATES_WAIT_H_

#include <state.h>

namespace EUSDAB
{
    namespace States
    {
        class Wait
        {
            public:
                Wait(Wait &&) = default;
                Wait(const Wait &) = default;
                Wait & operator=(const Wait &) = default;

                Wait(const Movement &, const Movement &);
                virtual ~Wait();

                virtual void onAnimationEnd();
        
            private:
                Movement _nextState;
        };
    }
}

#endif




