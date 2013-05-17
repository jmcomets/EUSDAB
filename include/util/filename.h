#ifndef UTIL_FILENAME_H_
#define UTIL_FILENAME_H_

#include <string>
#include <util/string.h>

namespace EUSDAB
{
    namespace Util
    {
        namespace Filename
        {
            // Cleanup a filename
            extern std::string clean(const std::string &);

            const std::string Separator = "/";

            // Variadic template : join (right, left...)
            //  by OS separator, eliminating duplicates and whitespace
            extern std::string join();
            // ...overload for specialization
            extern std::string join(const std::string & str);
            // ...also for c-string
            extern std::string join(const char * str);
            // ...variadic template
            template <typename... Args>
                std::string join(const std::string & left, Args ... args)
            {
                return String::rtrim(left, Separator + String::Whitespace)
                    + Separator + join(args...);
            }
        }
    }
}

#endif
