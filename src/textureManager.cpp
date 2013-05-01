#include <textureManager.h>
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
            std::pair<std::string, TexturePtr> empty_pair(filename, nullptr);
            auto insert_pair = inst->_textures.insert(empty_pair);
            if (insert_pair.second) // inserted -> new (not yet loaded)
            {
                auto it = insert_pair.first;
                TexturePtr ptr(it->second);
                sf::Texture * tx = new sf::Texture();
                if (tx->loadFromFile(filename))
                {
                    ptr.reset(tx);
                }
                else
                {
                    inst->_textures.erase(it);
                    throw std::runtime_error("Texture couldn't be loaded");
                }
                return ptr;
            }
            else
            {
                return insert_pair.first->second;
            }
        }
    }
}
