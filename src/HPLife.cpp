#include <HPLife.h>
#include <cassert>
#include <algorithm>

namespace EUSDAB
{
	HPLife::HPLife(const HPLife::Amount & min,
            const HPLife::Amount & max):
        Life(),
        _min(min), _max(max),
        _hp(max)
	{
        assert(_min <= _max);
	}

	bool HPLife::isAlive() const
	{
		return _hp > _min;
	}

	void HPLife::receiveDamage(const HPLife::Amount & dmg)
	{
        assert(dmg >= 0);
		_hp = std::max(_hp - dmg, _min);
	}

	void HPLife::healDamage(const HPLife::Amount & heal)
	{
        assert(heal >= 0);
        _hp = std::min(_hp + heal, _max);
	}
}
