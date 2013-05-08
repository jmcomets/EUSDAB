#include "tileset.h"

#include "textureManager.h"
#include "hitbox.h"

namespace Graphics {
    Tileset::Tileset(std::vector<Graphics::Sprite *> lsImg, std::vector<Geometry::Hitbox *> lsHB, std::time_t fpi) : _lsImage(lsImg), _lsHitbox(lsHB), _framePerImage(fpi)
    {
    }

    Tileset::~Tileset()
    {
        for (auto it : _lsImage)
            delete it;

        for (auto it : _lsHitbox)
            delete it;
    }

    std::vector<Sprite *> const & Tileset::lsImage() const
    {
        return _lsImage;
    }

    std::time_t Tileset::framePerImage() const
    {
        return _framePerImage;
    }
}

