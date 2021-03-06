#ifndef STATES_AERIALHIT_H
#define STATES_AERIALHIT_H

#include <state.h>

namespace EUSDAB
{
    namespace States
    {
        class AerialHit: public State
        {
            public:
                AerialHit(AerialHit &&) = default;
                AerialHit(const AerialHit &) = delete;
                AerialHit & operator=(const AerialHit &) = delete;

                AerialHit(Movement const &);
                virtual ~AerialHit();

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

                //void onEnter();
                //void onLeave();
        };
    }
}

#endif


