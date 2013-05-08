#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

#include <vector>
#include <memory>
#include <graphics.h>

namespace Graphics
{
    class TextureManager
    {
        public:
            TextureManager() = default;
            TextureManager(TextureManager &&) = default;
            TextureManager(const TextureManager &) = default;
            ~TextureManager();
            TextureManager & operator=(const TextureManager &) = default;
            const Texture * get(const char * raw, std::size_t size,
                    int x, int y, std::size_t width, std::size_t height);

        private:
            std::vector<std::shared_ptr<const Texture>> _pool;
    };
}

#endif
