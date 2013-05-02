#ifndef GRAPHICS_TEXTURE_MANAGER_H_
#define GRAPHICS_TEXTURE_MANAGER_H_

#include <string>
#include <memory>
#include <map>
#include <SFML/Graphics/Texture.hpp>

namespace EUSDAB
{
    namespace Graphics
    {
        class TextureManager
        {
            public:
                typedef std::shared_ptr<sf::Texture> TexturePtr;
                TextureManager(TextureManager &&) = delete;
                TextureManager(const TextureManager &) = delete;
                ~TextureManager() = default;
                TextureManager & operator=(const TextureManager &) = delete;

                static TexturePtr loadTexture(const std::string &);

            private:
                TextureManager();
                static TextureManager * instance();
                static std::shared_ptr<TextureManager> _instance;
                std::map<std::string, TexturePtr> _textures;
        };
    }
}

#endif
