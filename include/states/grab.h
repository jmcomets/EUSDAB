#ifndef STATES_STAND_H_
#define STATES_STAND_H_

#include <state.h>

namespace EUSDAB
{
    namespace States
    {
        class Stand: public State
        {
            public:
                Stand(Stand &&) = default;
                Stand(const Stand &) = delete;
                Stand & operator=(const Stand &) = delete;

                Stand(Movement const &);
                virtual ~Stand();
        };
    }
}

#endif


