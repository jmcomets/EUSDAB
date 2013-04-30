#ifndef ENTITY_PARSER_H_
#define ENTITY_PARSER_H_

#include <string>
#include <istream>
#include <entity.h>
#include <animation.h>

namespace EUSDAB
{
    class EntityParser
    {
        public:
            EntityParser() = default;
            EntityParser(EntityParser &&) = default;
            EntityParser(const EntityParser &) = default;
            EntityParser & operator=(const EntityParser &) = default;
            ~EntityParser() = default;

            Entity * loadEntity(const std::string &) const;
            Entity * readEntity(std::istream &, const std::string &) const;
            Animation * readAnimation(std::istream &, const std::string &) const;
    }; 
}

#endif
