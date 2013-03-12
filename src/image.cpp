#include <image.h>

namespace Graphics
{
    Image::Image(const Texture & texture):
        _sprite(new Sprite(texture))
    {
    }

    Image::~Image()
    {
    }

    const Sprite & Image::sprite() const
    {
        return *_sprite;
    }
}

