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

    Life::Ratio InfiniteLife::receiveDamage(const InfiniteLife::Amount &)
    {
        return static_cast<Life::Ratio>(0.0);
    }

    void InfiniteLife::healDamage(const InfiniteLife::Amount &)
    {
    }

    Life::Amount InfiniteLife::amount() const
    {
        return 42;
    }

    void InfiniteLife::reset()
    {

    }
}
