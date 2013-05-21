#ifndef STATES_AERIALDODGE_H
#define STATES_AERIALDODGE_H

#include <state.h>

namespace EUSDAB
{
    namespace States
    {
        class AerialDodge: public State
        {
            public:
                AerialDodge(AerialDodge &&) = default;
                AerialDodge(const AerialDodge &) = delete;
                AerialDodge & operator=(const AerialDodge &) = delete;

                AerialDodge(Movement const &);
                virtual ~AerialDodge();

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

                //void onEnter();
                //void onLeave();
                
                void setVelocity(const  Physics::Vector2 & );
                
                void onAnimationEnd();
                
            private:
            
                Physics::Vector2 _velocity;
        };
    }
}

#endif


