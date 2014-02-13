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

                void onLeft(const Event &);
                void onRight(const Event &);
                void onNextFrame();
                void onAnimationEnd();
                void onEnter();
                void onLeave();
                void setNextStateAnimationFrameToCurrentFrame() const;
        };
    }
}

#endif


