#ifndef _CYLINDER_
#define _CYLINDER_

#include "Capsule.hpp"

using namespace Core::Maths;


struct Cylinder
{
    Cylinder(Vec3 _point, Vec3 _normal, float _raduis, float _length)
     : point{_point}, normal{_normal}, raduis{_raduis}, length{_length} {};

    Cylinder(const Capsule &capsule)
     : point{capsule.point}, normal{capsule.direction}, raduis{capsule.raduis}, length{capsule.length} {};

    Core::Maths::Vec3 point;
    Core::Maths::Vec3 normal;

    float raduis;
    float length;
};

struct InfiniteCylinder
{
    InfiniteCylinder(Vec3 _point, Vec3 _normal, float _raduis) : point{_point}, normal{_normal}, raduis{_raduis} {};
    InfiniteCylinder(Cylinder cyl) : point{cyl.point}, normal{cyl.normal}, raduis{cyl.raduis} {};

    Core::Maths::Vec3 point;
    Core::Maths::Vec3 normal;

    float raduis;
};


#endif