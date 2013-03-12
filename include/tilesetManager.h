#ifndef TILESET_MANAGER_H_
#define TILESET_MANAGER_H_

#include <map>
#include <memory>
#include <graphics.h>
#include <textureManager.h>
#include <tileset.h>

namespace Graphics
{
    class TilesetManager
    {
        public:
            TilesetManager(TextureManager * = nullptr);
            TilesetManager(TilesetManager &&) = default;
            TilesetManager(const TilesetManager &) = default;
            ~TilesetManager() = default;
            TilesetManager & operator=(const TilesetManager &) = default;
            const Tileset * get(const std::string & filename);
            typedef std::shared_ptr<const Tileset> TilesetPtr;

        private:
            std::shared_ptr<TextureManager> _tm;
            std::map<std::string, TilesetPtr> _pool;
    };
}

#endif
