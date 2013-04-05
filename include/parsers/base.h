#ifndef ENTITY_PARSER_H_
#define ENTITY_PARSER_H_

#include <entity.h>
#include <physics/hitbox.h>

namespace EUSDAB
{
    namespace Parsers
    {
        class Base
        {
            public:
                Base(Base &&) = default;
                Base(const Base &) = default;
                Base & operator=(const Base &) = default;

                Base() = default;
                virtual ~Base();

                virtual Entity * readEntity(std::istream &) const = 0;
        };
    }
}

#endif
