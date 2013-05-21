#ifndef STATES_HIT_H
#define STATES_HIT_H

#include <state.h>

namespace EUSDAB
{
    namespace States
    {
        class Hit: public State
        {
            public:
                Hit(Hit &&) = default;
                Hit(const Hit &) = delete;
                Hit & operator=(const Hit &) = delete;

                Hit();
                virtual ~Hit();

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

                //void onAttack(const Event &);
                //void onDamage(const Event &);

                //void onGround(const Event &);

                //void onEnter();
                //void onLeave();

                void onAnimationEnd();
        };
    }
}

#endif


