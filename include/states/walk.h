#ifndef STATES_WALK_H
#define STATES_WALK_H

#include <states/motion.h>

namespace EUSDAB
{
    namespace States
    {
        class Walk: public Motion
        {
            public:
                Walk(Walk &&) = default;
                Walk(const Walk &) = delete;
                Walk & operator=(const Walk &) = delete;

                Walk(Movement const &);
                virtual ~Walk();

                void onUp(const Event &);
                void onLeft(const Event &);
                void onRight(const Event &);

                void onNextFrame();

                void onEnter();
        };
    }
}

#endif


