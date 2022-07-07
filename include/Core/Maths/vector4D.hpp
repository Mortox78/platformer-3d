#ifndef _VECTOR4D_
#define _VECTOR4D_

#include "vector3D.hpp"

namespace Core
{
    namespace Maths
    {
        class Vec4
        {
        public:
            float x{0};
            float y{0};
            float z{0};
            float w{0};
        
            Vec4    (){};
            Vec4    (const Vec3 &, float _w = 1.0f);
            Vec4    (float _x, float _y, float _z, float _w);
            ~Vec4   (){};
        
            Vec4    Homogenize();
            float   GetMagnitude() const;
            void    Normalize();
        };
    }
} // namespace Core

#endif