#include <fstream>
#include <sstream>
#include <tilesetManager.h>
#include <hitbox.h>
#include <point.h>

namespace Graphics
{
    TilesetManager::TilesetManager(TextureManager * tm):
        _tm(tm)
    {
        if (_tm == nullptr)
        {
            _tm.reset(new TextureManager());
        }
    }

    const Tileset * TilesetManager::get(const std::string & filename)
    {
        auto it = _pool.find(filename);
        if (it != _pool.end())
        {
            return it->second.get();
        }
        else
        {
            std::size_t nbrFrame;
            std::size_t width;
            std::size_t height;
            std::time_t framePerImage;
            int dx;
            int dy;

            std::ifstream f(filename.c_str(), std::ios::in);
            f >> nbrFrame >> width >> height >> framePerImage >> dx >> dy;

            Tileset * tileset = new Tileset(framePerImage);

            using namespace Geometry;
            for (std::size_t i = 0 ; i < nbrFrame ; ++i)
            {
                std::size_t nbPts;
                f >> nbPts;

                std::vector<Point<int>> pts;
                pts.reserve(nbPts);
                for (std::size_t j = 0 ; j < nbPts ; j++)
                {
                    int x, y;
                    f >> x >> y;
                    pts.emplace_back(Point<int>(x, y));
                }
                Hitbox * hb = new Hitbox(Polygone<int>(pts.begin(), pts.end()));
                tileset->addHitbox(hb);
            }

            std::string imgRaw;
            std::getline(f, imgRaw);
            std::stringstream buffer;
            buffer << f.rdbuf();
            imgRaw = buffer.str();
            for (std::size_t i = 0 ; i < nbrFrame ; ++i)
            {
                const Texture * tex = _tm->get(imgRaw.c_str(), imgRaw.size(), 0,
                        static_cast<int>(i * height), width, height);
                Sprite * sp = new Sprite(*tex);
                sp->setPosition(static_cast<float>(dx), static_cast<float>(dy));
                tileset->addSprite(sp);
            }
            f.close();
            _pool.insert(std::make_pair(filename, TilesetPtr(tileset)));
            return tileset;
        }
    }
}
