#include "tilesetManager.h"

#include <fstream>

#include "tileset.h"
#include "hitbox.h"
#include "point.h"

namespace Graphics
{
    TilesetManager * TilesetManager::s_instance = nullptr;

    TilesetManager::TilesetManager()
    {
    }

    TilesetManager::~TilesetManager()
    {
        for(auto it = s_pool.begin() ; it != s_pool.end() ; ++it)
            delete *it;
    }

    TilesetManager * TilesetManager::instance()
    {
        if(s_instance == nullptr)
            s_instance = new TilesetManager();
        return s_instance;
    }

    Tileset const * TilesetManager::get(std::string const & filename)
    {
        auto it = s_pool.find(filename);
        if(it != s_pool.end())
            return *it;

        size_t nbrFrame;
        size_t width;
        size_t height;
        time_t framePerImage;
        int dx;
        int dy;

        std::ifstream f(filename.c_str(), std::ios::in);
        f >> nbrFrame >> width >> height >> framePerImage >> dx >> dy;

        std::vector<Geometry::Hitbox *> lsHitbox;
        for (std::size_t i = 0 ; i < nbrFrame ; ++i)
        {
            size_t nbrPoint;
            f >> nbrPoint;

            std::vector<Geometry::Point> lsPoint;
            lsPoint.reserve(nbrPoint);
            for (std::size_t j = 0 ; j < nbrPoint ; j++)
            {
                int x, y;
                f >> x >> y;
                lsPoint.emplace_back(Geometry::Point(x, y));
            }

            lsHitbox.emplace_back(new Geometry::Hitbox(lsPoint));
        }

        std::string imgRaw;
        while(f.get(imgRaw));

        std::vector<Graphics::Sprite *> lsImage;
        for(std::size_t i = 0 ; i < nbrFrame ; ++i)
        {
            Graphics::Texture const * tex = TextureManager::get(imgRaw.c_str(), 0, i*height, width, height);
            lsImage.emplace_back(new Sprite(*tex, dx, dy));
        }

        f.close();

        Graphics::Tileset * t = new Graphics::Tileset(lsImage, lsHitbox, framePerImage);
        s_pool.insert(std::make_pair(filename, t));
        return t;
    }
}

