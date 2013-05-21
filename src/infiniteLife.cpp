#include <infiniteLife.h>

namespace EUSDAB
{
    InfiniteLife::InfiniteLife():
        Life()
    {
    }

    InfiniteLife::~InfiniteLife()
    {
    }

    bool InfiniteLife::isAlive() const
    {
        return true;
    }

    void InfiniteLife::receiveDamage(const InfiniteLife::Amount &)
    {
    }

    void InfiniteLife::healDamage(const InfiniteLife::Amount &)
    {
    }

    Life::Amount InfiniteLife::amount() const
    {
        return 42;
    }
}
