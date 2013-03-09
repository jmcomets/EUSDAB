#ifndef __TILESET_MANAGER_H__
#define __TILESET_MANAGER_H__

#include "graphics.h"

#include <map>

namespace Graphics
{
    class Tileset;

    class TilesetManager
    {
        public:
            virtual ~TilesetManager();

            TilesetManager * instance();

            Tileset const * get(std::string const & filename);

        protected:
            static TilesetManager * s_instance;

            typedef std::map<std::string, Tileset const *> pool_type;

            static pool_type s_pool;

        private:
            explicit TilesetManager();
            explicit TilesetManager(TilesetManager const &) = delete;
    };
}

#endif

