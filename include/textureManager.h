#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

#include "graphics.h"

namespace Graphics {
    class TextureManager {
        public:
            static TextureManager * instance();

            static Texture const * get(char const * raw, int x, int y, std::size_t width, std::size_t height);

            virtual ~TextureManager();

        private:
            explicit TextureManager();
            explicit TextureManager(TextureManager const &) = delete;

            typedef std::vector<Texture const *> pool_type;

            static TextureManager * s_instance;
            static pool_type s_pool;
    };
}

#endif

