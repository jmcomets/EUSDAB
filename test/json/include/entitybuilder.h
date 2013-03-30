#ifndef ENTITYBUILDER_H
#define ENTITYBUILDER_H

#include <string>
#include <entity.h>
#include <movement.h>
#include <input/state.h>

namespace EUSDAB
{
    class EntityBuilder
    {
        public:
            EntityBuilder() = default;
            EntityBuilder(EntityBuilder &) = default;
            EntityBuilder(const EntityBuilder &&) = default;
            ~EntityBuilder() = default;
            EntityBuilder & operator=(const EntityBuilder &&) = default;

            Entity * build() const;

        private:
            std::string _name;
            std::unordered_map<Movement, Input::State *> _states;
    };
}

#endif
