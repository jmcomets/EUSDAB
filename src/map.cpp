#include <map.h>

Map::Map(Map && m) : _view(std::move(m._view))
{
}

View Map::view()
{
    return _view;
}

