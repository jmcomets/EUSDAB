#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <input/event.h>

namespace EUSDAB 
{
    namespace Constants
    {
        typedef Input::Event::Ratio Ratio;
        static constexpr Ratio OnRunRatio = static_cast<Ratio>(0.85);
    }
}

#endif
