#include <percentageLife.h>
#include <cassert>
#include <algorithm>
#include <iostream>

namespace EUSDAB
{
	PercentageLife::PercentageLife(const Amount & min,
const Amount & max):
	Life(),
	_min(min), _max(max),
	_percentage(min)
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
		_percentage = std::min(_percentage + dmg, _max);
        std::cout << "Life : " << _percentage << "%" << std::endl;
	}

	void PercentageLife::healDamage(const Life::Amount & heal)
	{
        assert(heal >= 0);
        _percentage = std::max(_percentage + heal, _min);
	}
}
