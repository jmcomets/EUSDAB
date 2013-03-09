#ifndef POLYGONE_H_
#define POLYGONE_H_

#include <vector>
#include <point.h>

namespace Geometry
{
    template <typename T>
        class Polygone
    {
        public:
            template typename Iterator>
                Polygone(Iterator begin, Iterator end): _lsPoint(begin, end)
            {
            }
            Polygone(Polygone &&) = default;
            Polygone(const Polygone &) = default;
            ~Polygone() = default;
            Polygone & operator=(const Polygone &) = default;

        private:
            std::vector<Point<T>> _lsPoint;
    };
}

#endif
