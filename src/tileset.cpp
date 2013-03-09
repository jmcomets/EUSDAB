#include "tileset.h"

#include <fstream>

#include "textureManager.h"
#include "sprite.h"
#include "hitbox.h"
#include "point.h"

Tileset::Tileset(std::string const & filename) : _lsImage(), _lsHitbox(), _framePerImage(0)
{
    size_t nbrFrame;
    size_t width;
    size_t height;
    int dx;
    int dy;

    std::ifstream f(filename.c_str(), std::ios::in);
    f >> nbrFrame >> width >> height >> _framePerImage >> dx >> dy;
    for (std::size_t i = 0 ; i < nbrFrame ; ++i)
    {
        size_t nbrPoint;
        f >> nbrPoint;

        std::vector<Point> lsPoint;
        lsPoint.reserve(nbrPoint);
        for (std::size_t j = 0 ; j < nbrPoint ; j++)
        {
            int x, y;
            f >> x >> y;
            lsPoint.emplace_back(Point(x, y));
        }
    }

    std::string imgRaw;
    while(f.get(imgRaw));

    for(std::size_t i = 0 ; i < nbrFrame ; ++i)
    {
        const Texture * tex = TextureManager::get(imgRaw.c_str(), 0, i*height, width, height);
        _lsImage.emplace_back(new Sprite(tex, dx, dy));
    }

    f.close();
}

Tileset::~Tileset()
{
    for (auto it : _lsImage)
    {
        delete *it;
    }
}

std::vector<Sprite *> const & Tileset::lsImage() const
{
    return _lsImage;
}

std::time_t Tileset::framePerImage() const
{
    return _framePerImage;
}

