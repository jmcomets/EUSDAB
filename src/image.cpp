#include <image.h>

using namespace Graphics

Image::Image()
{
}

Image::Image(Texture const & texture);
{
    _sprite = new Sprite(texture);
}

Image::~Image()
{
    delete _sprite;
}

Sprite const & Image::sprite() const
{
    return *_sprite;
}

