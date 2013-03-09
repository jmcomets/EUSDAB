#include <map.h>

Map::Map(Map && m) : _view(std::move(m._view))
{
}

View Map::view()
{
    return _view;
}

string const & Map::name()
{
    return _name;
}

void Map::name(string const & name)
{
    _name = name;
}

void Map::addCharacter(Character * character)
{
    _characters.push_back(character);
}

void Map::removeCharacter(Character * character)
{
    std::remove(_characters.begin(), _characters.end(), character);
}

void Map::addPlatform(Plaform * platform)
{
    _platforms.push_back(platform);
}

void Map::removePlatform(Platform * platform)
{
    std::remove(_platforms.begin(), _platforms.end(), platform);
}

