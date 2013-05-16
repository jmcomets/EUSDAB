#ifndef INFINITE_LIFE_H_
#define INFINITE_LIFE_H_

#include <life.h>

namespace EUSDAB
{
	class InfiniteLife: public Life
	{
		public:
			InfiniteLife(InfiniteLife &&) = delete;
			InfiniteLife(const InfiniteLife &) = delete;
			InfiniteLife & operator=(const InfiniteLife &) =  delete;

			InfiniteLife();
			~InfiniteLife();

			bool isAlive() const;
			void receiveDamage(const Life::Amount &);
			void healDamage(const Life::Amount &);
	};
}

#endif
