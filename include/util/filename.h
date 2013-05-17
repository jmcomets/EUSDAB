#ifndef UTIL_FILENAME_H_
#define UTIL_FILENAME_H_

#include <string>
#include <util/string.h>
#include <iostream>

namespace EUSDAB
{
    namespace Util
    {
        namespace Filename
        {
            // Cleanup a filename
            extern std::string clean(const std::string &);

            // Variadic template : join (right, left...)
            //  by sep, eliminating duplicates and whitespace
            extern std::string join(const std::string &);
            // ...overload for specialization
            extern std::string join(const std::string & sep,
                    const std::string & str);
            // ...also for c-string
            extern std::string join(const std::string & sep,
                    const char * str);
            // ...variadic template
            template <typename... Args>
                std::string join(const std::string & sep,
                        const std::string & left, Args ... args)
            {
                std::string str = String::rtrim(left, sep + String::Whitespace)
                    + sep + join(sep, args...);
                std::cout << "variadic join(\"" << sep << "\", \"" << "\""
                    << left << "\", args...) -> \"" << str << "\"" << std::endl;
                return str;
            }
        }
    }
}

#endif
