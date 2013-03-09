#include "hitbox.h"

namespace Geometry
{
    Hitbox::Hitbox(Polygone<int> const & poly) : _polygone(poly)
    {
    }

    Hitbox::~Hitbox()
    {
    }
}

