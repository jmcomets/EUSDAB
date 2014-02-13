#ifndef STATES_RUN_H_
#define STATES_RUN_H_

#include <states/motion.h>

namespace EUSDAB
{
    namespace States
    {
        class Run: public Motion
        {
            public:
                Run(Run &&) = default;
                Run(const Run &) = delete;
                Run & operator=(const Run &) = delete;

                Run(Movement const &);
                virtual ~Run();

                void onUp(const Event &);
                void onDown(const Event &);
                void onLeft(const Event &);
                void onRight(const Event &);

                void onEnter();
        };
    }
}

#endif


