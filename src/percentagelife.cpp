#include <percentageLife.h>
#include <cassert>
#include <cmath>

namespace EUSDAB
{
	PercentageLife::PercentageLife(const PercentageLife::Amount & min,
const PercentageLife::Amount & max):
	Life(),
	_min(min), _max(max),
	_percentage(max)
	{
	assert(_min <= _max);
	}

	bool PercentageLife::isAlive() const
	{
		return true;
	}

	void PercentageLife::receiveDamage(const PercentageLife::Amount & dmg)
	{
	assert(dmg >= 0);
		_hp = std::min(percantage + dmg, _max);
	}

	void PercentageLife::healDamage(const Life::Amount & heal)
	{
        assert(heal >= 0);
        _hp = std::max(_hp + heal, _min);
	}
}
