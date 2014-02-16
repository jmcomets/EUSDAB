#ifndef LIFE_H_
#define LIFE_H_

namespace EUSDAB
{
    // Interface simulating a "life component", which would
    // allow dialog through damage / healing, and tell others
    // if it is "alive".
    class Life
    {
        public:
            Life() = default;
            Life(Life &&) = default;
            Life(const Life &) = default;
            virtual ~Life();
            Life & operator=(const Life &) = default;

            // Hide the underlying type for other classes
            typedef unsigned int Amount;
            typedef float Ratio;

            // Return if the life component is currently "alive",
            //  shouldn't modify the component.
            virtual bool isAlive() const = 0;

            // Receive damage (increase damage requested)
            virtual Ratio receiveDamage(const Amount &) = 0;

            // Heal damage (reduce damage requested)
            virtual void healDamage(const Amount &) = 0;

            virtual Amount amount() const = 0;

            // Restore all the life
            virtual void reset() = 0;
    };
}

#endif
