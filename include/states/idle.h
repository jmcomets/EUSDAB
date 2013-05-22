#ifndef STATES_IDLE_H
#define STATES_IDLE_H

#include <state.h>

namespace EUSDAB
{
    namespace States
    {
        class Idle: public State
        {
            public:
                Idle(Idle &&) = default;
                Idle(const Idle &) = delete;
                Idle & operator=(const Idle &) = delete;

                Idle(Movement const &);
                virtual ~Idle();

                void onUp(const Event &);
                void onDown(const Event &);
                void onLeft(const Event &);
                void onRight(const Event &);

                void onA(const Event &);
                void onB(const Event &);
                void onTrigger(const Event &);

                void onNextFrame();

                void setSlidingRatio(const Physics::Unit &);

            private:

                Physics::Unit _sliding_ratio;
        };
    }
}

#endif


