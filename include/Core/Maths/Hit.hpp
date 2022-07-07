#ifndef _HIT_
#define _HIT_

#include "vector3D.hpp"
#include <vector>

struct Hit
{
    Core::Maths::Vec3 point;
    Core::Maths::Vec3 normal;
};

struct Hits
{
    std::vector<Hit> list;
};


#endif