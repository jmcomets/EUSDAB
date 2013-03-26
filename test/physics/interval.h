#ifndef INTERVAL_H_
#define INTERVAL_H_

#ifndef RELEASE
#  include <iostream>
#endif

#include <algorithm>

namespace Utils
{
    template <class T>
        class Interval
    {
        public:
            Interval():
                _empty(true)
            {
                // FIXME: initialize (min, max)?
            }

            Interval(T a, T b):
                _empty(false),
                _min(std::min<T>(a, b)),
                _max(std::max<T>(a, b))
            {
            }

            Interval(Interval<T> &&) = default;
            Interval(const Interval<T> &) = default;
            ~Interval() = default;
            Interval & operator=(const Interval<T> &) = default;

            bool empty() const
            {
                return _empty;
            }

            Interval<T> merge(const Interval<T> & interval) const
            {
                // FIXME: doesn't work correctly when intersection is empty
                return Interval<T>(std::min<T>(_min, interval._min),
                        std::max<T>(_max, interval._max));
            }

            Interval<T> diff(const Interval<T> & interval) const
            {
#ifndef RELEASE
                std::cout << "(" << _min << ", " << _max << ") <diff> ("
                    << interval._min << ", " << interval._max << ") -> ";
#endif
                Interval<T> i;
                if ( !(*this < interval) && !(*this > interval) )
                {
                    i._min = std::max<T>(_min, interval._min);
                    i._max = std::min<T>(_max, interval._max);
                    i._empty = false;
#ifndef RELEASE
                    std::cout << "(" << i._min << ", " << i._max << ")";
#endif
                }
#ifndef RELEASE
                else
                {
                    std::cout << "<empty interval>";
                }
                std::cout << std::endl;
#endif
                return i;
            }

            bool intersects(const Interval<T> & interval) const
            {
                return diff(interval).empty() == false;
            }

            bool operator<(const Interval<T> & interval) const
            {
                return _max < interval._min;
            }

            bool operator>(const Interval<T> & interval) const
            {
                return _min > interval._max;
            }

        private:
            bool _empty;
            T _min, _max;
    };
}

#endif
