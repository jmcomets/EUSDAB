#include <texturemanager.h>
#include <stdexcept>
#include <iostream>

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

            /*
            TextureManager * inst = instance();
            std::pair<std::string, TexturePtr> empty_pair(filename, nullptr);
            auto insert_pair = inst->_textures.insert(empty_pair);
            if (insert_pair.second) // inserted -> new (not yet loaded)
            {
                std::cout << "IN TEXTURE MANAGER" << std::endl;
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
                std::cout << "THIS IS BULLSHIT !" << std::endl;
                return insert_pair.first->second;
            }
            //*/
        }
    }
}
