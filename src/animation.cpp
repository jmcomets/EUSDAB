#include <animation.h>

using namespace Graphics

Animation::Animation(std::vector<Texture *> const & textures) : _currentSpriteId(0)
{
    for(auto it : textures)
    {
        _sprites.push_back(new Sprite(**it));
    }
}

Animation::~Animation()
{
    for(auto it : _sprites)
    {
        delete *it;
    }
}

Sprite const & Animation::sprite() const
{
    _currentSpriteId %= _sprites.size();
    return *_sprite[_currentSpriteId++];
}

