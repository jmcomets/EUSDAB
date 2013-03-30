#include <entitywithmask.h>

namespace EUSDAB
{
    EntityWithMask::EntityWithMask():
        Entity(), _mask()
    {
    }

    EntityWithMask::~EntityWithMask()
    {
    }

    void EntityWithMask::mask(const Entity * e)
    {
        _mask.insert(e);
    }

    bool EntityWithMask::masked(const Entity * e) const
    {
        return _mask.find(e) != _mask.end();
    }

    void EntityWithMask::reset()
    {
        _mask.clear();
    }
}
