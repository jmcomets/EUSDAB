#include <HPLife.h>

namespace EUSDAB
{
	HPLife::HPLife()
	{
		hp = 100;
	}

	bool HPLife::isAlive() const
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

	void HPLife::receiveDamage(const Life::Amount & dmg)
	{
		hp-=dmg;
	}

	void HPLife::healDamage(const Life::Amount & heal)
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
