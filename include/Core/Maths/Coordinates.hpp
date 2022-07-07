#ifndef _COORDINATES_
#define _COORDINATES_

#include "vector3D.hpp"

#include <iostream>

namespace Core
{
    namespace Maths
    {
        namespace Coordinates
        {
            class Cylindical
            {
            public:
                float r     {0};
                float theta {0};
                float z     {0};

                Cylindical() = default;
                Cylindical(const Vec3 &vec);
                Cylindical(float _r, float _theta, float _z);
                ~Cylindical(){};

                Vec3 convertToCartesien();
                void convertToCylincal(const Vec3 &vec);

                void display(){std::cout << "r = " << r << ", theta = " << theta / (M_PI / 180) << ", z = " << z << std::endl;}
            };

            class Spherical
            {
            public:
                float r     {0};
                float theta {0};
                float phi   {0};

                Spherical() = default;
                Spherical(float _r, float _theta, float _phi);
                Spherical(const Vec3 &vec);
                ~Spherical(){};

                Vec3 convertToCartesien();
                void convertToSpherical(const Vec3 &vec);

                void display(){std::cout << "r = " << r << ", theta = " << theta / (M_PI / 180)  << ", phi = " << phi / (M_PI / 180) << std::endl;}
            };
        }
    }
} // namespace Coordinates



#endif