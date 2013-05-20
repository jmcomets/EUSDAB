#ifndef STATES_FALLING_H
#define STATES_FALLING _H

#include <state.h>

namespace EUSDAB
{
    namespace States
    {
        class Falling: public State
        {
            public:
                Falling(Falling &&) = default;
                Falling(const Falling &) = delete;
                Falling & operator=(const Falling &) = delete;

                Falling();
                virtual ~Falling();

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

                void onGround(const Event &);

                void onEnter();
                //void onLeave();
                
                void onChangeSide(const Movement & mvt);
                
                
                
            void setSpeed(Physics::Unit,Physics::Unit);
                
            private:
                
                Physics::Unit _speedX;
                Physics::Unit _speedY;

            protected:
                // Explicit helper method :)
                void setNextStateAnimationFrameToCurrentFrame() const;
                
                
        };
    }
}

#endif


