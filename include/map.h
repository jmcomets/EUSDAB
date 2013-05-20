#ifndef MAP_H_
#define MAP_H_

#include <string>
#include <list>
#include <utility>
#include <entity.h>
#include <graphics/texturemanager.h>
#include <physics/config.h>
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
			
			//animated background
			void addAnimatedBackground(Graphics::TextureManager::TexturePtr,Physics::Vector2);

		private:
			std::list<std::pair<sf::Sprite,Physics::Vector2>> _animatedBackgroundList;
	};
}

#endif
