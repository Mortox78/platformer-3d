#include "Plane.hpp"

using namespace Core::Maths;

Plane::Plane()
{
    normal = {0,0,0};
    distance = 0;
}

Plane::Plane(const Vec3& _normal, const float& _distance)
{
    normal      = _normal.Normalize();
    distance    = _distance;
}

Plane::Plane(const Vec3& P1, const Vec3& P2, const Vec3& P3)
{
    normal      = CrossProduct(P1 - P2, P1 - P3).Normalize();
    distance    = P1 * normal;
}

Plane::Plane(const Vec3& P, const Vec3& _normal)
{
    normal      = _normal;
    distance    = DotProduct(P, normal);
}



float Plane::GetSignedDistanceToPlane(const Vec3& P) const
{
    return distance - DotProduct(normal, P);
}

Vec3 Plane::GetClosestPointOnPlane(const Vec3& P) const
{
    return P + (normal * GetSignedDistanceToPlane(P));
}

bool Plane::GetSide(const Vec3& P) const
{
    return (normal * P >= distance);
}

bool Plane::IsOnPlane(const Vec3& P) const
{
    float result = normal * P;
    return (result > - TOLERANCE_ON_PLANE + distance && result <  TOLERANCE_ON_PLANE + distance);
}

bool Plane::Get3PlaneIntersection(const Plane& Plane1, const Plane& Plane2, const Plane& Plane3, Vec3& P)
{
    Matrix calcul(3,3);
    Matrix resOfCalc(3,1);

    calcul.accessor(1, 1) = Plane1.normal.x;
    calcul.accessor(1, 2) = Plane1.normal.y;
    calcul.accessor(1, 3) = Plane1.normal.z;

    calcul.accessor(2, 1) = Plane2.normal.x;
    calcul.accessor(2, 2) = Plane2.normal.y;
    calcul.accessor(2, 3) = Plane2.normal.z;

    calcul.accessor(3, 1) = Plane3.normal.x;
    calcul.accessor(3, 2) = Plane3.normal.y;
    calcul.accessor(3, 3) = Plane3.normal.z;

    if (calcul.determinant() == 0)
        return false;

    resOfCalc.accessor(1, 1) = Plane1.distance;
    resOfCalc.accessor(2, 1) = Plane2.distance;
    resOfCalc.accessor(3, 1) = Plane3.distance;
    
    Matrix result = Matrix::ResolveEquation(calcul, resOfCalc);

    P = {result.accessor(1,1), result.accessor(2,1), result.accessor(3,1)};

    return true;
}

void Plane::display()
{
    std::cout << "distance = " << distance << " / Normal : x = " << normal.x << ", y = " << normal.y << ", z = " << normal.z << std::endl;
}
