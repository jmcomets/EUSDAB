#ifndef __POLYGONE_H__
#define __POLYGONE_H__

#include <vector>

#include "point.h"

namespace Geometry
{
    template <typename T>
    class Polygone
    {
        public:
            explicit Polygone(std::vector<Point<T> > const & lsPoint) : _lsPoint(lsPoint) { }
            virtual ~Polygone() { }

        protected:
            std::vector<Point<T> > _lsPoint;
    };
}
#endif

