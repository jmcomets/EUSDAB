#include <util/filename.h>
#include <util/string.h>
#include <stdexcept>

namespace EUSDAB
{
    namespace Util
    {
        namespace Filename
        {
            std::string clean(const std::string & filename)
            {
                // First, trim any leading/trailing whitespace
                std::string trimmedOfWs = String::trim(filename);

                // At this point, base directory shouldn't be empty
                if (trimmedOfWs.empty())
                {
                    std::string msg("Invalid filename (is empty)");
                    throw std::runtime_error(msg);
                }

                // Trim trailing slashes
                std::string trimmedOfAll = String::rtrim(trimmedOfWs, "/");

                // At this point, base directory shouldn be empty only if
                //  path to "/" was specified
                return trimmedOfAll.empty() == false ? trimmedOfAll : "/";
            }

            std::string join(const std::string & sep, const std::string & str)
            {
                std::string ret_str = String::ltrim(str, sep);
                std::cout << "basic join(\"" << sep << "\", \"" << str
                    << "\") -> \"" << ret_str << "\"" << std::endl;
                return ret_str;
            }

            std::string join(const std::string & sep, const char * str)
            {
                return join(sep, std::string(str));
            }

            std::string join(const std::string & sep)
            {
                std::string str = "";
                std::cout << "empty join(\"" << sep << "\", \""
                    << "\") -> " << str << std::endl;
                return str;
            }
        }
    }
}
