#ifndef __HITBOX_H__
#define __HITBOX_H__

#include "polygone.h"

namespace Geometry
{
    class Hitbox
    {
        public:
            explicit Hitbox(Polygone const &);
            virtual ~Hitbox();

        protected:
            Polygone _polygone;
    }
}

#endif

