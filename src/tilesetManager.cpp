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

            std::vector<Geometry::Hitbox *> lsHitbox;
            for (std::size_t i = 0 ; i < nbrFrame ; ++i)
            {
                std::size_t nbrPoint;
                f >> nbrPoint;

                std::vector<Geometry::Point<int> > lsPoint;
                lsPoint.reserve(nbrPoint);
                for (std::size_t j = 0 ; j < nbrPoint ; j++)
                {
                    int x, y;
                    f >> x >> y;
                    lsPoint.emplace_back(Geometry::Point<int>(x, y));
                }
                lsHitbox.emplace_back(new Geometry::Hitbox(Geometry::Polygone<int>(lsPoint.begin(), lsPoint.end())));
            }

            std::string imgRaw;
            std::getline(f, imgRaw);
            std::stringstream buffer;
            buffer << f.rdbuf();
            imgRaw = buffer.str();

            std::vector<Sprite *> lsImage;
            for (std::size_t i = 0 ; i < nbrFrame ; ++i)
            {
                const Texture * tex = _tm->get(imgRaw.c_str(), imgRaw.size(), 0, static_cast<int>(i * height), width, height);
                lsImage.emplace_back(new Sprite(*tex));
                lsImage.back()->setPosition(static_cast<float>(dx), static_cast<float>(dy));
            }

            f.close();

            Tileset * t = new Tileset(lsImage, lsHitbox, framePerImage);
            _pool.insert(std::make_pair(filename, std::shared_ptr<const Tileset>(t)));
            return t;
        }
    }
}
