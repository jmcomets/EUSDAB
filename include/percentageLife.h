#define PERCENTAGELIFE_H_

namespace EUSDAB
{
	class PercentageLife : public Life
	{
		public:
			PercentageLife();
			PercentageLife(PercentageLife &&) = delete;
			PercentageLife(const PercentageLife &) = delete;
			PercentageLife & operator=(const PercentageLife &) =  delete;
			~InfiniteLife();

		protected:
			virtual bool isAlive();
			virtual bool receiveDamage(const Life::Amount & dmg);
			virtual bool healDamage(const Life::Amount & heal);
	}
}

#endif
