#ifndef JSON_ENTITY_PARSER_H_
#define JSON_ENTITY_PARSER_H_

#include <parsers/base.h>

namespace EUSDAB
{
    namespace Parsers
    {
        class Json: public Base
        {
            public:
                Json(Json &&) = default;
                Json(const Json &) = default;
                Json & operator=(const Json &) = default;
                Json() = default;
                virtual ~Json();

                virtual Entity * read(std::istream &) const;
        };
    }
}

#endif


