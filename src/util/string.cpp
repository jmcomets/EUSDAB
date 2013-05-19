#include <util/string.h>
#include <iostream>

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
                std::string str = srcStr.substr(srcStr.find_first_not_of(chars));
                std::cout << "ltrim(\"" << srcStr << "\") = " << str << std::endl;
                return str;
            }

            // Trim trailing chars
            std::string rtrim(const std::string & srcStr,
                    const std::string & chars)
            {
                std::string str = srcStr.substr(0, srcStr.find_last_not_of(chars) + 1);
                std::cout << "rtrim(\"" << srcStr << "\") = " << str << std::endl;
                return str;
            }

            // Trim both leading and trailing chars
            std::string trim(const std::string & srcStr,
                    const std::string & chars)
            {
                std::string str = rtrim(ltrim(srcStr, chars), chars);
                std::cout << "trim(\"" << srcStr << "\") = " << str << std::endl;
                return str;
            }
        }
    }
}
