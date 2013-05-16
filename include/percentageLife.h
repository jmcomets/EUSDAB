#ifndef PERCENTAGELIFE_H_
#define PERCENTAGELIFE_H_

#include <life.h>

namespace EUSDAB
{
	class PercentageLife : public Life
	{
		public:
			PercentageLife();
			PercentageLife(PercentageLife &&) = delete;
			PercentageLife(const PercentageLife &) = delete;
			PercentageLife & operator=(const PercentageLife &) =  delete;
			~PercentageLife();

			virtual bool isAlive() const;
			virtual void receiveDamage(const Life::Amount & dmg);
			virtual void healDamage(const Life::Amount & heal);
		protected:
			Life::Amount percentage;
	};
}

#endif
