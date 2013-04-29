#ifndef ENTITY_PARSER_H_
#define ENTITY_PARSER_H_

#include <entity.h>
#include <animation.h>

namespace EUSDAB
{
    class EntityParser: public Base
    {
        public:
            EntityParser() = default;
            EntityParser(EntityParser &&) = default;
            EntityParser(const EntityParser &) = default;
            EntityParser & operator=(const EntityParser &) = default;
            ~EntityParser() = default;

            virtual Entity * readEntity(std::istream &) const;
            virtual Animation * readAnimation(std::istream &) const;
    }; 
}

#endif
