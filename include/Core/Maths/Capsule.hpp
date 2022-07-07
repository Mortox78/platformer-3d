#ifndef _CAPSULE_
#define _CAPSULE_

#include "vector3D.hpp"

using namespace Core::Maths;

struct Capsule
{
    Capsule(){};
    Capsule(Vec3 _point, Vec3 _direction, float _raduis, float _length)
     : point{_point}, direction{_direction}, raduis{_raduis}, length{_length} {};  

    Vec3 point;
    Vec3 direction;

    float raduis;
    float length;
};


#endif