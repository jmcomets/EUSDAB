#ifndef STD_EXTENSION_H_
#define STD_EXTENSION_H_

#include <functional>

namespace std
{
    template <typename T>
        struct hash_ptr
    {
        size_t operator()(const T * x) const
        {
            return x != nullptr ? hash<T>()(*x) : 0;
        }
    };

    template <typename T>
        struct less_ptr
    {
        bool operator()(const T * l, const T * r) const
        {
            return l != nullptr && r != nullptr ? less<T>()(*l, *r) : false;
        }
    };
}

#endif
