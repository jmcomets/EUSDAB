#include <map.h>
#include <stdexcept>
#include <state.h>
#include <iostream>
#include <infiniteLife.h>

namespace EUSDAB
{
    Map::Map():
        Entity()
    {
        _gravitable =false;
        _life = new InfiniteLife();
        _nbrJumpMax = 0;
        _nbrJumpLeft = 0;
        _jumpPossible = false;
    }

    Map::~Map()
    {
    }

    void Map::addAnimatedBackground(Map::TexturePtr tx,
            const Physics::Vector2 & v)
    {
        assert(tx != nullptr);
        _animatedBackgroundList.emplace_back(sf::Sprite(*tx), v);
    }

    Map::SpriteList Map::getSprites()
    {
        SpriteList sprites;
        for (auto p : _animatedBackgroundList)
        {
            sprites.emplace_back(p.first);
        }
        return sprites;
    }

}
