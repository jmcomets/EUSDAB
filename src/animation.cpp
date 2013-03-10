#include <animation.h>

namespace Graphics
{
    Animation::Animation(Tileset const & tileset) : _tileset(tileset), _currentSpriteId(0)
    {
    }

    Animation::~Animation()
    {
    }

    void Animation::nextFrame()
    {
        _currentSpriteId++;
        _currentSpriteId %= _tileset.lsImage().size() * _tileset.framePerImage();
    }

    Sprite const & Animation::sprite() const
    {
        return *_tileset.lsImage()[static_cast<size_t>(_currentSpriteId * 1.0 / _tileset.framePerImage())];
    }
}

