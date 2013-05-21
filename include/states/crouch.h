#ifndef STATES_CROUCH_H
#define STATES_CROUCH_H

#include <state.h>

namespace EUSDAB
{
    namespace States
    {
        class Crouch: public State
        {
            public:
                Crouch(Crouch &&) = default;
                Crouch(const Crouch &) = delete;
                Crouch & operator=(const Crouch &) = delete;

                Crouch(Movement const &);
                virtual ~Crouch();

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
        };
    }
}

#endif


