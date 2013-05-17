#ifndef UTIL_STRING_H
#define UTIL_STRING_H

#include <string>

namespace EUSDAB
{
    namespace Util
    {
        namespace String
        {
            // Constant representing all whitespace
            extern const std::string Whitespace;

            // Trim leading chars from str
            extern std::string ltrim(const std::string & str,
                    const std::string & chars = Whitespace);

            // Trim trailing chars from str
            extern std::string rtrim(const std::string & str,
                    const std::string & chars = Whitespace);

            // Trim both leading and trailing chars from str
            extern std::string trim(const std::string & str,
                    const std::string & chars = Whitespace);
        }
    }
}

#endif
