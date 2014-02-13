#include <HPLife.h>
#include <cassert>
#include <algorithm>

namespace EUSDAB
{
    HPLife::HPLife(const HPLife::Amount & min, const HPLife::Amount & max):
        Life(), _hp(max), _min(min), _max(max)
    {
        assert(_min <= _max);
    }

    bool HPLife::isAlive() const
    {
        return _hp > _min;
    }

    Life::Ratio HPLife::receiveDamage(const HPLife::Amount & dmg)
    {
        _hp = std::max(_hp - dmg, _min);
        return 1.f * static_cast<Life::Ratio>(_hp)
            / static_cast<Life::Ratio>(_max);
    }

    void HPLife::healDamage(const HPLife::Amount & heal)
    {
        _hp = std::min(_hp + heal, _max);
    }

    Life::Amount HPLife::amount() const
    {
        return _hp;
    }
}
