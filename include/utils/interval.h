#ifndef INTERVAL_H_
#define INTERVAL_H_

#include <algorithm>

namespace Utils
{
    template <class T>
        class Interval
    {
        public:
            Interval():
                empty_(true)
            {
                // FIXME: initialize (min, max)?
            }

            Interval(T a, T b):
                empty_(false),
                min_(std::min<T>(a, b)),
                max_(std::max<T>(a, b))
            {
            }

            Interval(Interval<T> &&) = default;
            Interval(const Interval<T> &) = default;
            ~Interval() = default;
            Interval & operator=(const Interval<T> &) = default;

            bool empty() const
            {
                return empty_;
            }

            Interval<T> merge(const Interval<T> & interval) const
            {
                // FIXME: doesn't work correctly when intersection is empty
                return Interval<T>(std::min<T>(min_, interval.min_),
                        std::max<T>(max_, interval.max_));
            }

            Interval<T> diff(const Interval<T> & interval) const
            {
                if (*this < interval || *this > interval) // empty interval
                {
                    return Interval<T>();
                }
                else
                {
                    return Interval<T>(
                            std::max<T>(min_, interval.min_),
                            std::min<T>(max_, interval.max_)
                            );
                }
            }

            bool intersects(const Interval<T> & interval) const
            {
                return diff(interval).empty() == false;
            }

            bool operator<(const Interval<T> & interval) const
            {
                return max_ < interval.min_;
            }

            bool operator>(const Interval<T> & interval) const
            {
                return min_ > interval.max_;
            }

        private:
            bool empty_;
            T min_, max_;
    };
}

#endif
