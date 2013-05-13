#include <graphics/texturemanager.h>
#include <stdexcept>

namespace EUSDAB
{
    namespace Graphics
    {
        std::shared_ptr<TextureManager> TextureManager::_instance(nullptr);

        TextureManager::TextureManager():
            _textures()
        {
        }

        TextureManager * TextureManager::instance()
        {
            if (_instance.get() == nullptr)
            {
                _instance.reset(new TextureManager());
            }

            return _instance.get();
        }

        TextureManager::TexturePtr TextureManager::loadTexture(
                const std::string & filename)
        {
            TextureManager * inst = instance();
            auto it = inst->_textures.find(filename);
            if(it == inst->_textures.end()) // New texture
            {
                sf::Texture * tx = new sf::Texture();
                if(tx->loadFromFile(filename))
                {
                    TexturePtr ptr(tx);
                    inst->_textures.insert(std::make_pair(filename, ptr));
                    return ptr;
                }
                else
                {
                    throw std::runtime_error("Texture couldn't be loaded");
                }
            }
            else
            {
                return it->second;
            }
        }
    }
}
