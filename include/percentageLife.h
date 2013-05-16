#ifndef PERCENTAGELIFE_H_
#define PERCENTAGELIFE_H_

#include <life.h>

namespace EUSDAB
{
	class PercentageLife: public Life
	{
		public:
			PercentageLife();
			PercentageLife(PercentageLife &&) = delete;
			PercentageLife(const PercentageLife &) = delete;
			PercentageLife & operator=(const PercentageLife &) =  delete;
			~PercentageLife();

			bool isAlive() const;
			void receiveDamage(const Amount &);
			void healDamage(const Amount &);

		protected:
			Amount percentage;
	};
}

#endif
