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
            ~PercentageLife() = default;

            PercentageLife(const Amount & max,
                    const Amount & min = static_cast<Amount>(0));

            bool isAlive() const;
            Life::Ratio receiveDamage(const Amount &);
            void healDamage(const Amount &);
            virtual Life::Amount amount() const;
            virtual void reset();

        private:
            Amount _percentage;
            Amount _min;
            Amount _max;
    };
}

#endif
