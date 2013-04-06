#ifndef ENTITY_WITH_MASK_
#define ENTITY_WITH_MASK_

#include <set>
#include <entity.h>

namespace EUSDAB
{
    class EntityWithMask: public Entity
    {
        public:
            EntityWithMask(EntityWithMask &&) = default;
            EntityWithMask(EntityWithMask const &) = delete;
            EntityWithMask & operator=(EntityWithMask const &) = delete;

            EntityWithMask();
            virtual ~EntityWithMask();

            // Add an Entity to the current mask
            void mask(const Entity *);
            // ...range version
            template <typename InputIter>
                void mask(InputIter begin, InputIter end)
            {
                    for (; begin != end; begin++)
                    {
                        mask(*begin);
                    }
            }

            // Return if the Entity is masked
            bool masked(const Entity *) const;

            // Reset the mask, removing all masked Entities
            void reset();

        private:
            std::set<const Entity *> _mask;
    };
}

#endif
