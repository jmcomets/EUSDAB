#include <animation.h>

namespace Graphics
{
    Animation::Animation(const Tileset & tileset):
        _tileset(tileset), _index(0)
    {
    }

    Animation::~Animation()
    {
    }

    void Animation::nextFrame()
    {
        _index++;
        _index %= _tileset.lsImage().size()*_tileset.framePerImage();
    }

    const Sprite & Animation::sprite() const
    {
        return *_tileset.lsImage()[_index / _tileset.framePerImage()];
    }
}

