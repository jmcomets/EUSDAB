#ifndef __POLYGONE_H__
#define __POLYGONE_H__

#include <vector>

#include "point.h"

namespace Geometry
{
    class Polygone
    {
        public:
            explicit Polygone(std::vector<Point> const &);
            virtual ~Polygone();

        protected:
            std::vector<Point> _lsPoint;
    };
}
#endif

