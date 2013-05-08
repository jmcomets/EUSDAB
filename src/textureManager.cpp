#include <textureManager.h>

namespace Graphics
{
    TextureManager::~TextureManager()
    {
    }

    const Texture * TextureManager::get(const char * raw, std::size_t size, int x, int y, std::size_t width, std::size_t height)
    {
        sf::Image img;
        img.loadFromMemory(raw, size);
        sf::Texture * tex = new sf::Texture();
        tex->loadFromImage(img, sf::IntRect(x, y, static_cast<int>(width), static_cast<int>(height)));
        _pool.emplace_back(tex);
        return tex;
    }
}
