#include <animation.h>

namespace Graphics {
    Animation::Animation(Tileset const & tileset) : _tileset(tileset), _currentSpriteId(0)
    {
    }

    Animation::~Animation()
    {
    }

    Sprite const & Animation::sprite()
    {
        _currentSpriteId %= _tileset.lsImage().size();
        return *_tileset.lsImage()[_currentSpriteId++];
    }
}

