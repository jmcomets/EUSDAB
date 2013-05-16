#include <percentageLife.h>

namespace EUSDAB
{
	PercentageLife::PercentageLife()
	{
		percentage = 0;
	}

	bool PercentageLife::isAlive() const
	{
		return true;
	}

	void PercentageLife::receiveDamage(const Life::Amount & dmg)
	{
		percentage+=dmg;
	}

	void PercentageLife::healDamage(const Life::Amount & heal)
	{
		if (percentage > heal)
		{
			percentage-=heal;
		}
		else
		{
			percentage = 0;
		}
	}
}
