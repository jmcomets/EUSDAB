#ifndef STATES_JUMP_H
#define STATES_JUMP_H

#include <state.h>

namespace EUSDAB
{
    namespace States
    {
        class Jump: public State
        {
            public:
                Jump(Jump &&) = default;
                Jump(const Jump &) = delete;
                Jump & operator=(const Jump &) = delete;

                Jump();
                virtual ~Jump();

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
                
                void onMiddleOfJump();
                void onJumpEnd();

                //void onAttack(const Event &);
                //void onDamage(const Event &);

                void onGround(const Event &);

                void onEnter();
                
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


