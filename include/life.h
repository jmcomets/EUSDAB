#define LIFE_H_

namespace EUSDAB
{
	class Life
	{
		public:
			Life() = delete;
			Life(Life &&) = delete;
			Life(const Life &) = delete;
			Life & operator=(const Life &) = delete;
			~Life();

		protected:
			virtual bool isAlive() = 0;
			virtual bool receiveDamage(unsigned int amount) = 0;
			virtual bool healDamage(unsigned int amount) = 0;
			virtual int getHP() = 0;
	}
}

#endif
