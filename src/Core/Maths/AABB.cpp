#include "AABB.hpp"
#include "Math.hpp"
using namespace Core::Maths;
AABB::AABB() : center{Vec3(0, 0, 0)}, extendX{0}, extendY{0}, extendZ{0} {}
AABB::AABB(Vec3 _center, float _extendX, float _extendY, float _extendZ) :center{_center}, extendX{_extendX}, extendY{_extendY}, extendZ{_extendZ} 
{
    ref.origin = center;
}
AABB::~AABB() {}

bool AABB::SphereAndOrientedBoxAABBCollision(Sphere sphere, OrientedBox box)
{
    float extendX = box.extendX;
    float extendY = box.extendY;
    float extendZ = box.extendZ;
    box.ref.origin = box.position;

    Vec3 SphereLocalPos = box.ref.Point_World_To_Local(sphere.position);

    if (Core::Maths::Abs(SphereLocalPos.x) > extendX + sphere.ray || Core::Maths::Abs(SphereLocalPos.y) > extendY + sphere.ray || Core::Maths::Abs(SphereLocalPos.z) > extendZ + sphere.ray)
        return false;

    return true;
}

bool AABB::OrientedBoxAndOrientedBoxAABBCollision(OrientedBox box, OrientedBox box2)
{
    float boxExtendX = box.extendX;
    float boxExtendY = box.extendY;
    float boxExtendZ = box.extendZ;

    float box2ExtendX = box2.extendX;
    float box2ExtendY = box2.extendY;
    float box2ExtendZ = box2.extendZ;

     box.ref.origin = box.position;

    Vec3 box2LocalPos = box.ref.Point_World_To_Local(box2.position);

    if (Core::Maths::Abs(box2LocalPos.x) > boxExtendX + box2ExtendX ||
        Core::Maths::Abs(box2LocalPos.y) > boxExtendY + box2ExtendY ||
        Core::Maths::Abs(box2LocalPos.z) > boxExtendZ + box2ExtendZ)
        return false;

    return true;
}

bool AABB::PointAndAABBCollision(Vec3 pt)
{
    ref.origin = center;
    Vec3 localPos = ref.Point_World_To_Local(pt);
    if(Abs(localPos.x) > extendX || Abs(localPos.y) > extendY || Abs(localPos.z) > extendZ)
        return false;

    return true;
}