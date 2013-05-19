#include <util/string.h>

namespace EUSDAB
{
    namespace Util
    {
        namespace String
        {
            // Instanciation of "whitespace" constant
            const std::string Whitespace = " \t\r\n";

            // Trim leading chars
            std::string ltrim(const std::string & srcStr,
                    const std::string & chars)
            {
                return srcStr.substr(srcStr.find_first_not_of(chars));
            }

            // Trim trailing chars
            std::string rtrim(const std::string & srcStr,
                    const std::string & chars)
            {
                return srcStr.substr(0, srcStr.find_last_not_of(chars) + 1);
            }

            // Trim both leading and trailing chars
            std::string trim(const std::string & srcStr,
                    const std::string & chars)
            {
                return rtrim(ltrim(srcStr, chars), chars);
            }
        }
    }
}
