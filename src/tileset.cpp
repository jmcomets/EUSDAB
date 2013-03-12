#include <tileset.h>

namespace Graphics
{
    std::time_t Tileset::framesPerImage() const
    {
        return _fpi;
    }

    Tileset::SpritePtr Tileset::spriteAt(std::size_t index) const
    {
        return _images.at(index);
    }

    Tileset::HitboxPtr Tileset::hitboxAt(std::size_t index) const
    {
        return _hitboxes.at(index);
    }

    std::size_t Tileset::nbSprites() const
    {
        return _images.size();
    }

    std::size_t Tileset::nbHitboxes() const
    {
        return _hitboxes.size();
    }

    void Tileset::addSprite(Sprite * sp)
    {
        _images.emplace_back(sp);
    }

    void Tileset::addHitbox(Geometry::Hitbox * hb)
    {
        _hitboxes.emplace_back(hb);
    }
}
