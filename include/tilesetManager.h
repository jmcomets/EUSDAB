#ifndef TILESET_MANAGER_H_
#define TILESET_MANAGER_H_

#include <map>
#include <graphics.h>

namespace Graphics
{
    class Tileset;

    class TilesetManager
    {
        public:
            TilesetManager(const TilesetManager &) = delete;
            TilesetManager(TilesetManager &&) = delete;
            TilesetManager & operator=(const TilesetManager &) = delete;
            ~TilesetManager();
            static const Tileset * get(const std::string & filename);
            static void free();

        private:
            TilesetManager() = default;
            static TilesetManager * instance();
            static TilesetManager * _instance;
            std::map<std::string, const Tileset *> _pool;
    };
}

#endif

