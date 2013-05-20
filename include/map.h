#ifndef MAP_H_
#define MAP_H_

#include <list>
#include <entity.h>
#include <graphics/texturemanager.h>
#include <SFML/Graphics/Sprite.hpp>

namespace EUSDAB
{
    class Map: public Entity
    {
        public:
            Map(Map &&) = default;
            Map(Map const &) = delete;
            Map & operator=(Map const &) = delete;

            Map();
            virtual ~Map();

            typedef Graphics::TextureManager::TexturePtr TexturePtr;

            // Add animated background to the map
            void addAnimatedBackground(TexturePtr, const Physics::Vector2 &);

        private:
            std::list<std::pair<sf::Sprite, Physics::Vector2>> _animatedBackgroundList;
    };
}

#endif
