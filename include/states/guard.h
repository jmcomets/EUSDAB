#ifndef STATES_GUARD_H_
#define STATES_GUARD_H_

#include <state.h>

namespace EUSDAB
{
    namespace States
    {
        class Guard: public State
        {
            public:
                Guard(Guard &&) = default;
                Guard(const Guard &) = delete;
                Guard & operator=(const Guard &) = delete;

                Guard(Movement const &);
                virtual ~Guard();

                void onDown(const Event &);
                void onLeft(const Event &);
                void onRight(const Event &);

                void onTrigger(const Event &);

                void onAnimationEnd();
        };
    }
}

#endif


