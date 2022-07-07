#pragma once

#include "vector3D.hpp"

namespace Core
{
    namespace Maths
    {
        class Sphere
        {
            private:

            public:
                
                float ray;
                Vec3 position;

                Sphere();
                Sphere(Vec3 _position, float _ray);
                
                ~Sphere();
        };
    } // namespace Maths
} // namespace Core