#include "tileset.h"

#include "textureManager.h"
//#include "hitbox.h"
#include "point.h"

class Hitbox;

namespace Graphics {
    Tileset::Tileset(std::string const & filename) : _lsImage(), _lsHitbox(), _framePerImage(0)
    Tileset(std::vector<Sprite *> lsImage, std::vector<Hitbox *> lsHitbox, std::time_t framePerImage) : _lsImage(lsImage), _lsHitbox(lsHitbox), _framePerImage(framePerImage)
    {
    }

    Tileset::~Tileset()
    {
        for (auto it : _lsImage)
            delete *it;

        for (auto it : _lsHitbox)
            delete *it;
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

