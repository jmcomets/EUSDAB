#include <animation.h>
#include <iostream>

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
        Sprite * sp = _tileset.lsImage()[_currentSpriteId];
        std::cout << "La maman de Pierre à (" << sp->getPosition().x 
            << ", " << sp->getPosition().y << ") et est fat de ("
            << sp->getTexture()->getSize().x << ", " 
            << sp->getTexture()->getSize().y << ")" << std::endl;
        return *sp;
    }
}

