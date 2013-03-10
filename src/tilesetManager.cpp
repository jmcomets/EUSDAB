#include <fstream>
#include <tilesetManager.h>
#include <textureManager.h>
#include <tileset.h>
#include <hitbox.h>
#include <point.h>

namespace Graphics
{
    TilesetManager * TilesetManager::_instance = nullptr;

    TilesetManager::~TilesetManager()
    {
        for (auto p : _pool)
        {
            delete p.second;
        }
    }

    TilesetManager * TilesetManager::instance()
    {
        if (_instance == nullptr)
        {
            _instance = new TilesetManager();
        }
        return _instance;
    }

    const Tileset * TilesetManager::get(const std::string & filename)
    {
        TilesetManager * tm = instance();
        auto it = tm->_pool.find(filename);
        if (it != tm->_pool.end())
        {
            return it->second;
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
            while (f >> imgRaw);

            std::vector<Graphics::Sprite *> lsImage;
            for (std::size_t i = 0 ; i < nbrFrame ; ++i)
            {
                const Graphics::Texture * tex = Graphics::TextureManager::get(imgRaw.c_str(), imgRaw.size(), 0, static_cast<int>(i * height), width, height);
                lsImage.emplace_back(new Sprite(*tex));
                lsImage.back()->setPosition(static_cast<float>(dx), static_cast<float>(dy));
            }

            f.close();

            Graphics::Tileset * t = new Graphics::Tileset(lsImage, lsHitbox, framePerImage);
            tm->_pool.insert(std::make_pair(filename, t));
            return t;
        }
    }

    void TilesetManager::free()
    {
        delete _instance;
        _instance = nullptr;
    }
}

#ifndef NO_RAII

namespace Priv
{
    static struct RAII
    {
        ~RAII()
        {
            Graphics::TilesetManager::free();
        }
    } raii;
}

#endif

