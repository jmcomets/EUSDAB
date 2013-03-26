#ifndef INTERVAL_H_
#define INTERVAL_H_

#include <algorithm>

namespace Geometry
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

            Interval(const Interval<T> & interval):
                empty_(interval.empty_),
                min_(interval.min_),
                max_(interval.max_)
            {
            }

            virtual ~Interval()
            {
            }

            Interval & operator=(const Interval<T> & interval)
            {
                empty_ = interval.empty_;
                min_ = interval.min_;
                max_ = interval.max_;
                return *this;
            }

            inline bool empty() const
            {
                return empty_;
            }

            inline Interval<T> merge(const Interval<T> & interval) const
            {
                // FIXME: doesn't work correctly when intersection is empty
                return Interval<T>(std::min<T>(min_, interval.min_),
                        std::max<T>(max_, interval.max_));
            }

            inline Interval<T> diff(const Interval<T> & interval) const
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

            inline bool intersects(const Interval<T> & interval) const
            {
                return diff(interval).empty() == false;
            }

            inline bool operator<(const Interval<T> & interval) const
            {
                return max_ < interval.min_;
            }

            inline bool operator>(const Interval<T> & interval) const
            {
                return min_ > interval.max_;
            }

        private:
            bool empty_;
            T min_, max_;
    }; // class Interval
} // namespace Geometry

#endif // INTERVAL_H_INCLUDED_
