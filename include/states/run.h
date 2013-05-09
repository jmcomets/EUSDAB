#ifndef STATES_RUN_H
#define STATES_RUN_H

#include <state.h>

namespace EUSDAB
{
    namespace States
    {
        class Run: public State
        {
            public:
                Run(Run &&) = default;
                Run(const Run &) = delete;
                Run & operator=(const Run &) = delete;

                Run();
                virtual ~Run();

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


