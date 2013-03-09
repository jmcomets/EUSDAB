#ifndef HITBOX_H_
#define HITBOX_H_

#include <polygone.h>

namespace Geometry
{
    class Hitbox
    {
        public:
            Hitbox(const Polygone<int> &);
            virtual ~Hitbox();

        private:
            Polygone<int> _polygone;
    };
}

#endif
