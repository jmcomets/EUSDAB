#include "textureManager.h"

#include <SFML/Graphics.hpp>

namespace Graphics
{
    TextureManager * TextureManager::_instance = nullptr;

    TextureManager::~TextureManager()
    {
        for (auto p : _pool)
        {
            delete p;
        }
    }

    Texture const * TextureManager::get(char const * raw, std::size_t size, int x, int y, std::size_t width, std::size_t height)
    {
        sf::Image img;
        img.loadFromMemory(static_cast<void const *>(raw), size);
        sf::Texture * tex = new sf::Texture();
        tex->loadFromImage(img, sf::IntRect(x, y, static_cast<int>(width), static_cast<int>(height)));
        instance()->_pool.emplace_back(tex);
        return tex;
    }

    TextureManager * TextureManager::instance()
    {
        if (_instance == nullptr)
        {
            _instance = new TextureManager();
        }

        return _instance;
    }

    void TextureManager::free()
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
            Graphics::TextureManager::free();
        }
    } raii;
}

#endif
