#ifndef STATES_STUNNED_H_
#define STATES_STUNNED_H_

#include <state.h>

namespace EUSDAB
{
    namespace States
    {
        class Stunned: public State
        {
            public:
                Stunned(Stunned &&) = default;
                Stunned(const Stunned &) = delete;
                Stunned & operator=(const Stunned &) = delete;

                Stunned(Movement const &);
                virtual ~Stunned();
                void onAnimationEnd();
        };
    }
}

#endif


