#ifndef INFINITELIFE_H_
#define INFINITELIFE_H_

#include <life.h>

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
			virtual bool isAlive() const;
			virtual void receiveDamage(const Life::Amount & dmg);
			virtual void healDamage(const Life::Amount & heal);
	};
}

#endif
