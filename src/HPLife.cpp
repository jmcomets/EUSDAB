#include <HPLife.h>

namespace EUSDAB
{
	HPLife::HPLife()
	{
		hp = 100;
	}

	HPLife::isAlive()
	{
		if (hp > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	HPLife::receiveDamage(const Life::Amount & dmg)
	{
		hp-=dmg;
	}

	HPLife::healDamage(const Life::Amount & heal)
	{
		if (hp < 100-heal)
		{
			hp+=heal;
		}
		else
		{
			hp = 100;
		}
	}
}
