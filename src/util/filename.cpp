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

            std::string join(const std::string & str)
            {
                return String::ltrim(str);
            }

            std::string join(const char * str)
            {
                return join(std::string(str));
            }

            std::string join()
            {
                return "";
            }
        }
    }
}
