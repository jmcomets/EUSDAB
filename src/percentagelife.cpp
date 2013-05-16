#include <percentageLife.h>

namespace EUSDAB
{
	percentageLife::PercentageLife()
	{
		hp = 100;
	}

	PercentageLife::isAlive()
	{
		return true;
	}

	HPLife::receiveDamage(const Life::Amount & dmg)
	{
		percentage+=dmg;
	}

	HPLife::healDamage(const Life::Amount & heal)
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
