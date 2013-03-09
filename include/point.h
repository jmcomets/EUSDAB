#ifndef POINT_H_
#define POINT_H_

namespace Geometry
{
    template <typename T>
    class Point
    {
        public:
            Point():
                Point(0, 0)
            {
            }

            Point(const T & x, const T & y):
                _x(x), _y(y)
            {
            }
            
            Point(Point &&) = default;
            Point(const Point &) = default;
            ~Point() = default;
            Point & operator=(const Point &) = default;

            const T & x() const
            {
                return _x;
            }

            const T & x(const T & x)
            {
                return _x = x;
            }

            const T & y() const
            {
                return _y;
            }

            const T & y(const T &)
            {
                return _y = y;
            }

        private:
            T _x, _y;
    };
}

#endif
