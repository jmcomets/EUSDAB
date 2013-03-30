#ifndef ENTITY_WITH_MASK_
#define ENTITY_WITH_MASK_

#include <unordered_set>
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

            template <typename InputIter>
                void mask(InputIter begin, InputIter end)
            {
                    typedef typename InputIter::value_type V;
                    static_assert(std::is_convertible<const Entity *, V>::value, 
                            "Can only mask `const Entity &`");
                    for (; begin != end; begin++)
                    {
                        mask(*begin);
                    }
            }
            void mask(const Entity *);
            bool masked(const Entity *) const;

            void reset();

        private:
            std::unordered_set<const Entity *> _mask;
    };
}

#endif
