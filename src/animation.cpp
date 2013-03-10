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
        _currentSpriteId %= _tileset.lsImage().size();
    }

    Sprite const & Animation::sprite() const
    {
        return *_tileset.lsImage()[_currentSpriteId];
    }
}

