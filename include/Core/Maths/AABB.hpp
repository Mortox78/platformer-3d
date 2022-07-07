#pragma once

#include "vector3D.hpp"
#include "OrientedBox.hpp"
#include "Sphere.hpp"
#include "referential.hpp"

namespace Core
{
    namespace Maths
    {
        class AABB
        {
            public:
                Vec3 center;
                float extendX, extendY, extendZ;
                Referential ref;
                AABB();
                AABB(Vec3 _center, float _extendX, float _extendY, float _extendZ);
                ~AABB();
                static bool SphereAndOrientedBoxAABBCollision(Sphere sphere, OrientedBox box);
                static bool OrientedBoxAndOrientedBoxAABBCollision(OrientedBox box, OrientedBox box2);
                bool PointAndAABBCollision(Vec3 pt);
        };
    } // namespace Maths
} // namespace Core