#ifndef STATES_GUARD_H
#define STATES_GUARD_H

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

                Guard();
                virtual ~Guard();

                void onUp(const Event &);
                void onDown(const Event &);
                void onLeft(const Event &);
                void onRight(const Event &);

                void onA(const Event &);
                void onB(const Event &);
                //void onX(const Event &);
                //void onY(const Event &);
                //void onZ(const Event &);
                void onTrigger(const Event &);

                void onNextFrame();

                //void onAttack(const Event &);
                //void onDamage(const Event &);

                //void onGround(const Event &);
                
                void onAnimationEnd();

                void onEnter();
                void onLeave();
                
                
                private:
                
        };
    }
}

#endif


