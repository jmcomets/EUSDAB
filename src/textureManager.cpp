#include "textureManager.h"

#include <SFML/Graphics.hpp>

namespace Graphics
{
    TextureManager * TextureManager::s_instance = nullptr;

    TextureManager::TextureManager()
    {
    }

    TextureManager::~TextureManager()
    {
        for(auto it = s_pool.begin() ; it != s_pool.end() ; ++it)
            delete *it;
    }

    Texture const * TextureManager::get(char const * raw, std::size_t size, int x, int y, std::size_t width, std::size_t height)
    {
        sf::Image img;
        img.loadFromMemory(static_cast<void const *>(raw), size);
        sf::Texture tex = new sf::Texture();
        tex->loadFromImage(img, sf::IntRect(x, y, width, height));
        return tex;
    }

    TextureManager * TextureManager::instance()
    {
        if(s_instance == nullptr)
            s_instance = new TextureManager();

        return s_instance;
    }
}
