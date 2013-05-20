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
        _animatedBackgroundList.push_back(std::make_pair(sf::Sprite(*tx), v));
    }
}
