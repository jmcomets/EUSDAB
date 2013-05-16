#define INFINITELIFE_H_

namespace EUSDAB
{
	class InfiniteLife : public Life
	{
		public:
			InfiniteLife();
			InfiniteLife(InfiniteLife &&) = delete;
			InfiniteLife(const InfiniteLife &) = delete;
			InfiniteLife & operator=(const InfiniteLife &) =  delete;
			~InfiniteLife();

		protected:
			virtual bool isAlive();
			virtual bool receiveDamage(const Life::Amount & dmg);
			virtual bool healDamage(const Life::Amount & heal);
	}
}

#endif
