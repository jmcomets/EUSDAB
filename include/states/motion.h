#ifndef STATES_MOTION_H_
#define STATES_MOTION_H_

#include <physics/config.h>
#include <movement.h>
#include <state.h>

namespace EUSDAB
{
    namespace States
    {
        class Motion: public State
        {
            public:
                Motion(Motion &&) = default;
                Motion(const Motion &) = default;
                Motion & operator=(const Motion &) = default;

                Motion(const Movement &);
                ~Motion();
                
                // Set the velocity
                void setVelocity(const Physics::Vector2 &);

                // Switch state, keeping the velocity
                void switchStateWithVelocity(const Movement::Flag &);

                virtual void onA(const Event &);
                virtual void onB(const Event &);

                virtual void onNextFrame();
        
            protected:
                Physics::Vector2 _velocity;
        };
    }
}

#endif
