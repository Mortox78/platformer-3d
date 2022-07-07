#ifndef _PLANE_
#define _PLANE_

#include "vector3D.hpp"
#include "matrix.hpp"
#include "Line.hpp"

#include <vector>

#define TOLERANCE_ON_PLANE 0.01

using namespace Core::Maths;

namespace Core
{
    namespace Maths
    {
        class Plane
        {
        public:
            Vec3 normal;
            float distance;

            Plane();
            Plane(const Vec3& _normal, const float& _distance);
            Plane(const Vec3& P1, const Vec3& P2, const Vec3& P3);
            Plane(const Vec3& P, const Vec3& _normal);
            ~Plane(){};

            float           GetSignedDistanceToPlane(const Vec3& P) const;
            Vec3            GetClosestPointOnPlane(const Vec3& P) const;
            bool            GetSide(const Vec3& P) const;
            bool            IsOnPlane(const Vec3& P) const;
            static bool     Get3PlaneIntersection(const Plane& Plane1, const Plane& Plane2, const Plane& Plane3, Vec3& P);

            static std::vector<Vec3> MouvementFrom3Point(const Vec3& A, const Vec3& B, const Vec3& C, float detail = 10);

            void display();
        };
    }
}

#endif