#ifndef HPLIFE_H_
#define HPLIFE_H_

#include <life.h>

namespace EUSDAB
{
	class HPLife : public Life
	{
		public:
			HPLife();
			HPLife(HPLife &&) = delete;
			HPLife(const HPLife &) = delete;
			HPLife & operator=(const HPLife &) =  delete;
			~HPLife();

		
			virtual bool isAlive() const;
			virtual void receiveDamage(const Life::Amount & dmg);
			virtual void healDamage(const Life::Amount & heal);
		protected:
			Life::Amount hp;
	};
}

#endif
