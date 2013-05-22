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

                Falling(Movement const &);
                virtual ~Falling();

                void onUp(const Event &);
                void onLeft(const Event &);
                void onRight(const Event &);

                void onA(const Event &);
                void onB(const Event &);
                void onGround(const Event &);

                void setVelocity(const  Physics::Vector2 & );

            protected:
                // Explicit helper method :)
                void setNextStateAnimationFrameToCurrentFrame() const;
                
            private:
                Physics::Vector2 _velocity;
        };
    }
}

#endif


