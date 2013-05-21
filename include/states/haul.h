#ifndef STATES_STAND_H
#define STATES_STAND_H

#include <state.h>

namespace EUSDAB
{
    namespace States
    {
        class Stand: public State
        {
            public:
                Stand(Stand &&) = default;
                Stand(const Stand &) = delete;
                Stand & operator=(const Stand &) = delete;

                Stand(Movement const &);
                virtual ~Stand();

                void onUp(const Event &);
                void onDown(const Event &);
                void onLeft(const Event &);
                void onRight(const Event &);

                void onA(const Event &);
                void onB(const Event &);
                //void onX(const Event &);
                //void onY(const Event &);
                //void onZ(const Event &);
                //void onTrigger(const Event &);

                void onNextFrame();

                //void onAttack(const Event &);
                //void onDamage(const Event &);

                //void onGround(const Event &);

                void onEnter();
                void onLeave();

                void onAnimationEnd();
        };
    }
}

#endif


