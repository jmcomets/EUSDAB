#ifndef STATES_STUNNED_H
#define STATES_STUNNED_H

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


