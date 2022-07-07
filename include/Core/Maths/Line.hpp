#ifndef _LINE_
#define _LINE_

#include "vector3D.hpp"
#include "Segment.hpp"

namespace Core
{
    namespace Maths
    {
        class Line
        {
        public:
            Vec3 point;
            Vec3 direction;

            Line();
            Line(const Segment &seg);
            Line(const Vec3 &_point, const Vec3 &_direction);
            ~Line();
        };
    }
}

#endif