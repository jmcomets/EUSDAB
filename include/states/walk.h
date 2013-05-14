#ifndef STATES_WALK_H
#define STATES_WALK_H

#include <state.h>

namespace EUSDAB
{
    namespace States
    {
        class Walk: public State
        {
            public:
                Walk(Walk &&) = default;
                Walk(const Walk &) = delete;
                Walk & operator=(const Walk &) = delete;

                Walk();
                virtual ~Walk();

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
                //void onLeave();
        };
    }
}

#endif


