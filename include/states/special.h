#ifndef STATES_SPECIAL_H
#define STATES_SPECIAL_H

#include <state.h>

namespace EUSDAB
{
    namespace States
    {
        class Special: public State
        {
            public:
                Special(Special &&) = default;
                Special(const Special &) = delete;
                Special & operator=(const Special &) = delete;

                Special(Movement const &);
                virtual ~Special();

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

                void onGround(const Event &);

                void onEnter();
                void onLeave();

        };
    }
}

#endif


