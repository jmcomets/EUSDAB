#ifndef ENTITY_PARSER_H_
#define ENTITY_PARSER_H_

#include <map>
#include <string>
#include <istream>
#include <entity.h>
#include <animationparser.h>

namespace EUSDAB
{
    class EntityParser
    {
        public:
            EntityParser(EntityParser &&) = default;
            EntityParser(const EntityParser &) = default;
            EntityParser & operator=(const EntityParser &) = default;
            ~EntityParser() = default;

            EntityParser(const std::string &);

            // Load from Entity directory
            Entity * loadEntity(const std::string &);

            // Read from stream with Entity directory given
            Entity * readEntity(std::istream &, const std::string &);

            // Get base directory
            std::string baseDirectory() const;

        private:
            std::string _baseDirectory;
            std::map<std::string, AnimationParser> _animationParsers;
    }; 
}

#endif
