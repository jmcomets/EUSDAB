#ifndef PERCENTAGELIFE_H_
#define PERCENTAGELIFE_H_

#include <life.h>

namespace EUSDAB
{
	class PercentageLife: public Life
	{
		public:
			PercentageLife(PercentageLife &&) = default;
			PercentageLife(const PercentageLife &) = default;
			PercentageLife & operator=(const PercentageLife &) =  default;
			~PercentageLife();

			PercentageLife(const Amount & max,
                    const Amount & min = static_cast<Amount>(0));

			bool isAlive() const;
			void receiveDamage(const Amount &);
			void healDamage(const Amount &);

		private:
			Amount _min, _percentage, _max;
	};
}

#endif
