#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

#include <graphics.h>

namespace Graphics
{
    class TextureManager
    {
        public:
            TextureManager(TextureManager &&) = delete;
            TextureManager(const TextureManager &) = delete;
            ~TextureManager();
            TextureManager & operator=(const TextureManager &) = delete;
            static const Texture * get(const char * raw, std::size_t size, int x, int y, std::size_t width, std::size_t height);

        private:
            static TextureManager * instance();
            TextureManager();

            static TextureManager * _instance;
            std::vector<const Texture *> _pool;
    };
}

#endif
