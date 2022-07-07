#include "referential.hpp"

using namespace Core::Maths;

Referential::Referential() : i{Vec3(1, 0, 0)}, j{Vec3(0, 1, 0)}, k{Vec3(0, 0, 1)}, origin{Vec3(0,0,0)} {}
Referential::Referential(Vec3 _i, Vec3 _j, Vec3 _k, Vec3 _origin) : i{_i}, j{_j}, k{_k}, origin{_origin}{}
Referential::~Referential(){}


Vec3 Referential::Point_Local_To_World(Vec3 point) const
{
    return Vec3(point.x * i.x + point.y * j.x + point.z * k.x + origin.x,
                point.x * i.y + point.y * j.y + point.z * k.y + origin.y,
                point.x * i.z + point.y * j.z + point.z * k.z + origin.z);
}

Vec3 Referential::Point_World_To_Local(Vec3 point) const
{
    point = point - origin;
    return Vec3(point * i, point * j, point * k);
}

Vec3 Referential::Vector_Local_To_World(Vec3 vec) const
{
    return Vec3(vec.x * i.x + vec.y * j.x + vec.z * k.x,
                vec.x * i.y + vec.y * j.y + vec.z * k.y,
                vec.x * i.z + vec.y * j.z + vec.z * k.z);
}

Vec3 Referential::Vector_World_To_Local(Vec3 vec) const
{
    return Vec3(vec * i, vec * j, vec * k);
}






Vec3 Referential::PointLocalToWorld(Vec3 point) const
{
    return Vec3(point.x * i.x + point.y * j.x + point.z * k.x + origin.x,
                point.x * i.y + point.y * j.y + point.z * k.y + origin.y,
                point.x * i.z + point.y * j.z + point.z * k.z + origin.z);
}

Vec3 Referential::PointWorldToLocal(Vec3 point) const
{
    point = point - origin;
    return Vec3(point * i, point * j, point * k);
}

Vec3 Referential::VectorLocalToWorld(Vec3 vec) const
{
    return Vec3(vec.x * i.x + vec.y * j.x + vec.z * k.x,
                vec.x * i.y + vec.y * j.y + vec.z * k.y,
                vec.x * i.z + vec.y * j.z + vec.z * k.z);
}

Vec3 Referential::VectorWorldToLocal(Vec3 vec) const
{
    return Vec3(vec * i, vec * j, vec * k);
}