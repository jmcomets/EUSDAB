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
        _index %= _tileset.nbSprites()*_tileset.framesPerImage();
    }

    const Sprite & Animation::sprite() const
    {
        return *_tileset.spriteAt(_index / _tileset.framesPerImage());
    }
}

