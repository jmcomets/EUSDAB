#include <states/stand.h>
#include <constants.h>

namespace EUSDAB
{
    namespace States
    {
        Stand::Stand(Movement const & m):
            State(m)
        {
        }

        Stand::~Stand()
        {
        }
    }
}
