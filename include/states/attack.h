#ifndef STATES_ATTACK_H
#define STATES_ATTACK_H

#include <state.h>

namespace EUSDAB
{
    namespace States
    {
        class Attack: public State
        {
            public:
                Attack(Attack &&) = default;
                Attack(const Attack &) = delete;
                Attack & operator=(const Attack &) = delete;

                Attack(Movement const &);
                virtual ~Attack();

                void onUp(const Event &);
                void onDown(const Event &);
                void onLeft(const Event &);
                void onRight(const Event &);

                //void onA(const Event &);
                //void onB(const Event &);
                //void onX(const Event &);
                //void onY(const Event &);
                //void onZ(const Event &);
                //void onTrigger(const Event &);

                void onNextFrame();

                void onAnimationEnd();

                //void onAttack(const Event &);
                //void onDamage(const Event &);

                //void onGround(const Event &);

                void onEnter();
                void onLeave();

                void setSlidingRatio(Physics::Unit);

            private:

                Physics::Unit _sliding_ratio;


        };
    }
}

#endif


