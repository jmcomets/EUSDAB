#ifndef ENTITY_PARSER_H_
#define ENTITY_PARSER_H_

#include <string>
#include <istream>
#include <entity.h>
#include <animationparser.h>

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

            // Load from Entity directory
            Entity * loadEntity(const std::string &) const;
            Animation * loadAnimation(const std::string &) const;

            // Read from stream with Entity directory given
            Entity * readEntity(std::istream &, const std::string &) const;
            Animation * readAnimation(std::istream &, const std::string &) const;

        private:
            AnimationParser _animParser;
    }; 
}

#endif
