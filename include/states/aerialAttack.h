#ifndef STATES_AERIALATTACK_H
#define STATES_AERIALATTACK_H

#include <state.h>

namespace EUSDAB
{
    namespace States
    {
        class AerialAttack: public State
        {
            public:
                AerialAttack(AerialAttack &&) = default;
                AerialAttack(const AerialAttack &) = delete;
                AerialAttack & operator=(const AerialAttack &) = delete;

                AerialAttack(Movement const &);
                virtual ~AerialAttack();

                void onAnimationEnd();
                void onLeave();
        };
    }
}

#endif


