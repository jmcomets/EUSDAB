#ifndef __POINT_H__
#define __POINT_H__

namespace Geometry
{
    template <typename T>
    class Point
    {
        public:
            explicit Point(T const & x, T const & y);
            virtual ~Point();

            T const & x() const;
            T const & y() const;

            void setX(T const &);
            void setY(T const &);

        protected:
            T _x;
            T _y;
    };
}

#endif

