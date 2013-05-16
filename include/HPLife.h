#define HPLIFE_H_

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

		protected:
			virtual bool isAlive();
			virtual bool receiveDamage(const Life::Amount & dmg);
			virtual bool healDamage(const Life::Amount & heal);

			Life::Amount hp;
	}
}

#endif
