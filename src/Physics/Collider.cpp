#include "Collider.hpp"
#include "Math.hpp"
#include "vector3D.hpp"
#include "referential.hpp"

#include <iostream>

#define SMALL_NUM 0.00000001
#include "SphereCollider.hpp"
#include "OrientedBoxCollider.hpp"
#include "Assertion.hpp"

using namespace Physics;
using namespace Core::Maths;

// Collider::Collider() : AdditionalBehavior(), type{ColliderType::COLLIDER} {}
std::vector<Collider *> Collider::allCollider;

Collider::Collider() : AdditionalBehavior(), type{ColliderType::COLLIDER}
{
    allCollider.push_back(this);
}

ColliderType Collider::Type() const
{
    return type;
}

void Collider::Start(Physics::Transform *trs)
{
    transform = trs;
}

bool Collider::CheckCollisionWithAllCollider(Collider *collider)
{
    unsigned int listSize = allCollider.size();
    for (unsigned int i = 0; i < listSize; i++)
    {
        if (collider != allCollider[i])
        {
            if(SimpleCheckCollide(collider, allCollider[i]))
            {
                return true;
            }
        }
    }
    return false;
}

bool Collider::SimpleCheckCollide(const Collider *collider1, const Collider *collider2, bool AABBCheck)
{
    if (collider1->Type() == ColliderType::SPHERE && collider2->Type() == ColliderType::ORIENTED_BOX)
    {
        if (AABBCheck)
        {
        }
        bool test = IsSphereAndOrientedBoxCollide(((SphereCollider *)collider1)->GetSphere(), ((OrientedBoxCollider *)collider2)->GetOrientedBox());
            
        return test;
    }
    return false;
}


bool Collider::IsSphereAndOrientedBoxCollide(Core::Maths::Sphere sphere, Core::Maths::OrientedBox box)
{
    //std::cout << "Collide Sphere Box" << std::endl;
    //std::cout << "x = " << sphere.transform.position.x << ", y = " << sphere.transform.position.y << ", z = " << sphere.transform.position.z << std::endl;
    //std::cout << "x = " << box.transform.position.x << ", y = " << box.transform.position.y << ", z = " << box.transform.position.z << std::endl;
    box.ref.origin = box.position;

    Core::Maths::Vec3 pointOfCollision;
    Core::Maths::Vec3 LocalSpherePos = box.ref.Point_World_To_Local(sphere.position);

    pointOfCollision.x = Core::Maths::Clamp(LocalSpherePos.x, -box.extendX, box.extendX);
    pointOfCollision.y = Core::Maths::Clamp(LocalSpherePos.y, -box.extendY, box.extendY);
    pointOfCollision.z = Core::Maths::Clamp(LocalSpherePos.z, -box.extendZ, box.extendZ);

    float distance = (LocalSpherePos - pointOfCollision).GetMagnitude();

    if (distance < sphere.ray)
        return true;
    else
        return false;
}

bool Collider::IsSegmentAndPlaneCollide(const Segment &seg, const Plane &plane, Hit &hit)
{
    if (DotProduct(seg.GetVector(), plane.normal) == 0) // check if the vector of the segment isn't ortogonal to the plan
    {
        return false;
    }
    
    // I try to find the value t for which the distance between the point of the segment and the plane is 0

    float t = (plane.distance - ((plane.normal.x * seg.A.x) + (plane.normal.y * seg.A.y) + (plane.normal.z * seg.A.z)))
    / ((plane.normal.x * (seg.B.x - seg.A.x)) + (plane.normal.y * (seg.B.y - seg.A.y)) + (plane.normal.z * (seg.B.z - seg.A.z)));

    if (t > 1 || t < 0)
    {
        return false;
    }

    hit.point = seg.A + (seg.GetVector() * t);
    
    if (plane.GetSide(seg.A) >= 0)
    {
        hit.normal = plane.normal.Normalize();
    }
    else
    {
        hit.normal = plane.normal.Normalize() * (-1);
    }
    
    return true;
}

bool Collider::IsSegmentIntersectionQuad(const Segment& segment, Quad& quad, Hit& hit)
{    
    Plane plane(quad.ref.origin, quad.ref.k);

    Hit hitPlane;

    if (IsSegmentAndPlaneCollide(segment, plane, hitPlane)) // if the segment collide with the plane on the quad
    {
        Vec3 localHit = quad.ref.PointWorldToLocal(hitPlane.point); // Set the collision point on the referential of the quad if is within the range of the quad

        if (abs(localHit.x) < quad.extendX && abs(localHit.y) < quad.extendY)
        {
            hit = hitPlane;
            hit.normal.Normalize();
            return true;
        }
    }
    return false;
}

bool Collider::IsSegmentIntersectingSphere(const Segment &segment, const Sphere &sphere, Hit &hit)
{
    if (DistanceSqrFromPointToSegment(sphere.position, segment) > pow(sphere.ray, 2))
    {
        return false;
    }

    Segment localSeg; // Set the segment in the range of the sphere so I can use the equation x² + y² + z² = R²

    localSeg.A = segment.A - sphere.position;
    localSeg.B = segment.B - sphere.position;


    float C = pow(localSeg.A.x, 2) + pow(localSeg.A.y, 2) + pow(localSeg.A.z, 2) - pow(sphere.ray, 2);
    float B = 2 * (localSeg.A.x * (localSeg.B.x - localSeg.A.x) + localSeg.A.y * (localSeg.B.y - localSeg.A.y) + localSeg.A.z * (localSeg.B.z - localSeg.A.z));
    float A = pow((localSeg.B.x - localSeg.A.x), 2) + pow((localSeg.B.y - localSeg.A.y), 2) + pow((localSeg.B.z - localSeg.A.z), 2);
    float delta = pow(B, 2) - (4 * A * C);

    if (delta > 0)
    {   
        // I use the smaller useable t value found to be sure that I got the closest intersection Point

        float t = (-B + sqrt(delta)) / (2*A);
        float t2 = (-B - sqrt(delta)) / (2*A);

        if ((t >= 0 && t <= 1) && (t2 >= 0 && t2 <= 1))
        {
            hit.point = segment.A + (segment.GetVector() * std::min(t, t2));
            hit.normal = (hit.point - sphere.position).Normalize();
            return true;
        }
        else if (t >= 0 && t <= 1) 
        {
            hit.point  = segment.A + (segment.GetVector() * t);
            hit.normal = (hit.point - sphere.position).Normalize();
            return true;
        }
        else if (t2 >= 0 && t2 <= 1) 
        {
            hit.point = segment.A + (segment.GetVector() * t2);
            hit.normal = (hit.point - sphere.position).Normalize();
            return true;
        }   
    }    
    return false;
}

bool Collider::IsSegmentIntersectingInfiniteCylinder(const Segment &seg, const InfiniteCylinder &cylinder, Hit &hit)
{
    Plane plane(cylinder.point, cylinder.normal);

    Segment segOnPlane;

    segOnPlane.A = plane.GetClosestPointOnPlane(seg.A);
    segOnPlane.B = plane.GetClosestPointOnPlane(seg.B);

    Vec3 closestPoint = ClosestPointToSegment(cylinder.point, segOnPlane);

    if (DistanceSqrFromPointToSegment(cylinder.point, segOnPlane) < pow(cylinder.raduis, 2))
    {    
        Referential refCylinder;
    
        refCylinder.origin = cylinder.point;
    
        refCylinder.k = (cylinder.normal).Normalize();
        if (segOnPlane.A == Vec3(0,0,0))
        {
            refCylinder.i = (segOnPlane.B - cylinder.point).Normalize();
        }
        else
        {
            refCylinder.i = (segOnPlane.A - cylinder.point).Normalize();            
        }
        refCylinder.j = CrossProduct(refCylinder.i, refCylinder.k).Normalize();
    
        Segment localSeg; // Set the segment in the range of the sphere so I can use the equation x² + y² = R²
    
        localSeg.A = refCylinder.PointWorldToLocal(seg.A);
        localSeg.B = refCylinder.PointWorldToLocal(seg.B);


        float C = pow(localSeg.A.x, 2) + pow(localSeg.A.y, 2) - pow(cylinder.raduis, 2);
        float B = 2 * (localSeg.A.x * (localSeg.B.x - localSeg.A.x) + localSeg.A.y * (localSeg.B.y - localSeg.A.y));
        float A = pow((localSeg.B.x - localSeg.A.x), 2) + pow((localSeg.B.y - localSeg.A.y), 2);
    
        float delta = pow(B, 2) - (4 * A * C);
        
        if (delta > 0) //I use the smaller useable t value found to be sure that I got the closest intersection Point
        {   
            float t = (-B + sqrt(delta)) / (2*A);
            float t2 = (-B - sqrt(delta)) / (2*A);

            if ((t >= 0 && t <= 1) && (t2 >= 0 && t2 <= 1))
            {
                hit.point = seg.A + seg.GetVector() * std::min(t, t2);
                hit.normal = (hit.point - ClosestPointToLine(hit.point, Line(cylinder.point, cylinder.normal))).Normalize();
                return true;
            }
            else if (t >= 0 && t <= 1) 
            {
                hit.point = seg.A + seg.GetVector() * t;
                hit.normal = (hit.point - ClosestPointToLine(hit.point, Line(cylinder.point, cylinder.normal))).Normalize();
                return true;
            }
            else if (t2 >= 0 && t2 <= 1) 
            {   
                hit.point = seg.A + seg.GetVector() * t2;
                hit.normal = (hit.point - ClosestPointToLine(hit.point, Line(cylinder.point, cylinder.normal))).Normalize();
                return true;
            }   
        }
    }   
    return false;
}


bool Collider::IsSegmentIntersectingCylinder(const Segment &seg, const Cylinder &cylinder, Hit &hit)
{
    Hit tempHit;

    Plane plane(cylinder.point, cylinder.normal);

    Segment segOnPlane;

    segOnPlane.A = plane.GetClosestPointOnPlane(seg.A);
    segOnPlane.B = plane.GetClosestPointOnPlane(seg.B);

    // Create the cylinder referential

    Referential refCylinder;
    refCylinder.origin = cylinder.point;
    
    refCylinder.k = (cylinder.normal).Normalize();
    if (segOnPlane.A == Vec3(0,0,0))
    {
        refCylinder.i = (segOnPlane.B - cylinder.point).Normalize();
    }
    else
    {
        refCylinder.i = (segOnPlane.A - cylinder.point).Normalize();            
    }
    refCylinder.j = CrossProduct(refCylinder.i, refCylinder.k).Normalize();
    

    //Create a segment that will be used for comparaision to the cylinder

    Segment localSeg;
    localSeg.A = refCylinder.PointWorldToLocal(seg.A);
    localSeg.B = refCylinder.PointWorldToLocal(seg.B);

    // Check if both point arend to far from the height of the cylinder

    if (localSeg.A.z > cylinder.length/2 && localSeg.B.z > cylinder.length/2)
    {
        return false;
    }
    else if ((localSeg.A.z < (- cylinder.length)/2) && (localSeg.B.z < (- cylinder.length)/2))
    {
        return false;
    }    

    // When both point are inside the infinite cylinder
    if ((segOnPlane.A - cylinder.point).GetSqrMagnitude() <= pow(cylinder.raduis, 2) && (segOnPlane.B - cylinder.point).GetSqrMagnitude() <= pow(cylinder.raduis, 2))
    {
        int direction = 1; // use to determine which side of the cylinder must be checked to find t

        if (localSeg.A.z < 0)
        {
            direction = -1;
        }
        else if (localSeg.A.z == 0)
        {
            if ((localSeg.B.z - localSeg.A.z) == 0)
            {
                return false;
            }
            else
            {
                direction = (localSeg.B.z - localSeg.A.z) / abs(localSeg.B.z - localSeg.A.z);
            }
        }
        float t = ((direction * cylinder.length/2) - localSeg.A.z) / (localSeg.B.z - localSeg.A.z);

        if (t >= 0 && t <= 1) 
        {
            hit.point = seg.A + (seg.GetVector() * t);
            hit.normal = cylinder.normal * direction;
            return true;
        }
            else
        {
            return false;
        }  
    }    
    else if (IsSegmentIntersectingInfiniteCylinder(seg, cylinder, tempHit))
    {
         Vec3 hitLocal = refCylinder.PointWorldToLocal(tempHit.point);

        if (abs(hitLocal.z) > (cylinder.length / 2)) // if the collide point is outside of the cylinder
        {
            int direction = 1;

            if (localSeg.A.z > localSeg.B.z)
            {
                direction = -1;
            }

            float t = ((direction * cylinder.length/2) - localSeg.A.z) / (localSeg.B.z - localSeg.A.z);

            if (t >= 0 && t <= 1) 
            {
                hit.point = seg.A + (seg.GetVector() * t);
                return true;
            }
            else
            {
                return false;
            }  
        }
        else
        {
            hit = tempHit;
            return true;
        }   
    }
    return false;
}

bool Collider::IsSegmentIntersectingCapsule(const Segment &seg, const Capsule &capsule, Hit &hit)
{
    // Create the cylinder referential
    Plane planeCenterCapsule(capsule.point, capsule.direction);
    
    Segment segOnPlane;

    segOnPlane.A = planeCenterCapsule.GetClosestPointOnPlane(seg.A);
    segOnPlane.B = planeCenterCapsule.GetClosestPointOnPlane(seg.B);

    Vec3 closestPoint = ClosestPointToSegment(capsule.point, segOnPlane);

    if ((closestPoint - capsule.point).GetSqrMagnitude() > pow(capsule.raduis, 2))
    {
        return false;
    }

    Hit tempHit;

    if (IsSegmentIntersectingCylinder(seg, capsule, tempHit)) // Collision with the cylinder inside the capsule
    {
        // check if there could be a could be a collision with one of the sphere of the capsule
        if (planeCenterCapsule.GetSignedDistanceToPlane(tempHit.point) >= capsule.length/2)
        {
            return IsSegmentIntersectingSphere(seg, Sphere(capsule.point + (capsule.direction * (capsule.length/2)), capsule.raduis), hit);
        }
        else if (planeCenterCapsule.GetSignedDistanceToPlane(tempHit.point) <= -capsule.length/2)
        {
            return IsSegmentIntersectingSphere(seg, Sphere(capsule.point + (capsule.direction * (-capsule.length/2)), capsule.raduis), hit);
        }
        else
        {
            hit = tempHit;
            return true;
        }
    }
    else // if there isn't a collision with the cylinder I check for both of the sphere
    {
        if (IsSegmentIntersectingSphere(seg, Sphere(capsule.point + (capsule.direction * (capsule.length/2)), capsule.raduis), tempHit))
        {
            hit = tempHit;
            return true;
        }
        else if (IsSegmentIntersectingSphere(seg, Sphere(capsule.point + (capsule.direction * (-capsule.length/2)), capsule.raduis), tempHit))
        {
            hit = tempHit;
             return true;
        }
        
    }
    return false;   

}

bool Collider::IsSegmentAndAABBCollide(const Segment &seg, const AABB &aabb, Hit &hit)
{
    Referential refX({0,0,1}, {0,1,0}, {1,0,0}, aabb.center);
    Referential refY({1,0,0}, {0,0,1}, {0,1,0}, aabb.center);
    Referential refZ({0,0,1}, {1,0,0}, {0,0,1}, aabb.center);

    Quad quadX(refX, aabb.extendZ, aabb.extendY);
    Quad quadY(refY, aabb.extendX, aabb.extendZ);
    Quad quadZ(refZ, aabb.extendY, aabb.extendY);


    Vec3 localPos = seg.A - aabb.center;
    Vec3 localPosB = seg.B - aabb.center;

    float posMult = 1;

    if (abs(localPos.x) <= aabb.extendX && abs(localPos.y) <= aabb.extendY && abs(localPos.z) <= aabb.extendZ
    && abs(localPosB.x) <= aabb.extendX && abs(localPosB.y) <= aabb.extendY && abs(localPosB.z) <= aabb.extendZ)
    {
        return false;
    }

    // check Y faces

    quadY.ref.origin = quadY.ref.origin + quadY.ref.k * (aabb.extendY);
    if (IsSegmentIntersectionQuad(seg, quadY, hit))
    {
        return true;
    }

    quadY.ref.origin = quadY.ref.origin + quadY.ref.k * (aabb.extendY * (-2));
    if (IsSegmentIntersectionQuad(seg, quadY, hit))
    {
        return true;
    }
    
    // check X faces

    quadX.ref.origin = quadX.ref.origin + quadX.ref.k * (aabb.extendX);
    if (IsSegmentIntersectionQuad(seg, quadX, hit))
    {
        return true;
    }

    quadX.ref.origin = quadX.ref.origin + quadX.ref.k * (aabb.extendX * (-2));
    if (IsSegmentIntersectionQuad(seg, quadX, hit))
    {
        return true;
    }

    // check Z faces

    quadZ.ref.origin = quadZ.ref.origin + quadZ.ref.k * (aabb.extendZ);
    if (IsSegmentIntersectionQuad(seg, quadZ, hit))
    {
        return true;
    }

    quadZ.ref.origin = quadZ.ref.origin + quadZ.ref.k * (aabb.extendZ * (-2));
    if (IsSegmentIntersectionQuad(seg, quadX, hit))
    {
        return true;
    }
    
    return false;
}

bool Collider::IsSegmentAndOrientedBoxCollide(const Segment &seg, const OrientedBox &box, Hit &hit)
{
    Referential refX({0,0,1}, {0,1,0}, {1,0,0}, box.ref.origin);
    Referential refY({1,0,0}, {0,0,1}, {0,1,0}, box.ref.origin);
    Referential refZ({0,0,1}, {1,0,0}, {0,0,1}, box.ref.origin);

    Quad quadX(refX, box.extendZ, box.extendY);
    Quad quadY(refY, box.extendX, box.extendZ);
    Quad quadZ(refZ, box.extendY, box.extendY);

    Segment localSeg;

    localSeg.A = box.ref.PointWorldToLocal(seg.A);
    localSeg.B = box.ref.PointWorldToLocal(seg.B);

    //Vec3 localPos = localSeg.A - box.ref.origin;

    Vec3 localPos  = localSeg.A - box.ref.origin;
    Vec3 localPosB = localSeg.B - box.ref.origin;

    if (abs(localPos.x) <= box.extendX && abs(localPos.y) <= box.extendY && abs(localPos.z) <= box.extendZ
    && abs(localPosB.x) <= box.extendX && abs(localPosB.y) <= box.extendY && abs(localPosB.z) <= box.extendZ)
    {
        return false;
    }

    // check Y faces

    quadY.ref.origin = quadY.ref.origin + quadY.ref.k * (box.extendY);
    if (IsSegmentIntersectionQuad(seg, quadY, hit))
    {
        return true;
    }

    quadY.ref.origin = quadY.ref.origin + quadY.ref.k * (box.extendY * (-2));
    if (IsSegmentIntersectionQuad(seg, quadY, hit))
    {
        return true;
    }
    
    // check X faces

    quadX.ref.origin = quadX.ref.origin + quadX.ref.k * (box.extendX);
    if (IsSegmentIntersectionQuad(seg, quadX, hit))
    {
        return true;
    }

    quadX.ref.origin = quadX.ref.origin + quadX.ref.k * (box.extendX * (-2));
    if (IsSegmentIntersectionQuad(seg, quadX, hit))
    {
        return true;
    }

    // check Z faces

    quadZ.ref.origin = quadZ.ref.origin + quadZ.ref.k * (box.extendZ);
    if (IsSegmentIntersectionQuad(seg, quadZ, hit))
    {
        return true;
    }

    quadZ.ref.origin = quadZ.ref.origin + quadZ.ref.k * (box.extendZ * (-2));
    if (IsSegmentIntersectionQuad(seg, quadX, hit))
    {
        return true;
    }
    
    return false;
}

bool Collider::GetFirstCollisionPointBetweenMovingSphereAndStaticBox(const OrientedBox& box, const Sphere &sphere, const Vec3 &seg, float deltaTime, Hit &hit)
{
    Capsule capX(box.ref.origin, box.ref.i, sphere.ray, box.extendX);
    Capsule capY(box.ref.origin, box.ref.j, sphere.ray, box.extendY);
    Capsule capZ(box.ref.origin, box.ref.k, sphere.ray, box.extendZ);

    Referential refX(box.ref.k, box.ref.j, box.ref.i, box.ref.origin);
    Referential refY(box.ref.i, box.ref.k, box.ref.j, box.ref.origin);
    Referential refZ(box.ref.j, box.ref.i, box.ref.k, box.ref.origin);

    Quad quadX(refX, box.extendZ, box.extendY);
    Quad quadY(refY, box.extendX, box.extendZ);
    Quad quadZ(refZ, box.extendY, box.extendY);

    Vec3 localPos = box.ref.PointWorldToLocal(sphere.position);

    Segment segment(sphere.position, sphere.position + (seg * deltaTime));

    // check for the Y faces

    if (abs(localPos.y) >= box.extendY)
    {
        float posMultY = 1;

        if (localPos.y <= -box.extendY)
        {
            posMultY = -1;
        }

        quadY.ref.origin = quadY.ref.origin + quadY.ref.k * ((posMultY) * (box.extendY + sphere.ray));

        if (IsSegmentIntersectionQuad(segment, quadY, hit))
        {
            return true;
        }
        
        Capsule tempCap = capX;
        tempCap.point = tempCap.point + (box.ref.j * (posMultY * box.extendY) + box.ref.k * box.extendZ);

        if (IsSegmentIntersectingCapsule(segment, tempCap, hit))
        {
            return true;
        }

        tempCap.point = tempCap.point - (box.ref.k * (box.extendZ * 2));
        
        if (IsSegmentIntersectingCapsule(segment, tempCap, hit))
        {
            return true;
        }

        tempCap = capZ;
        tempCap.point = tempCap.point + (box.ref.j * (posMultY * box.extendY) + box.ref.i * box.extendX);
        if (IsSegmentIntersectingCapsule(segment, tempCap, hit))
        {
            return true;
        }

        tempCap.point = tempCap.point - (box.ref.i * (box.extendX * 2));
        
        if (IsSegmentIntersectingCapsule(segment, tempCap, hit))
        {
            return true;
        }
    }
    
    // check X faces
    
    if (abs(localPos.x) >= box.extendX)
    {
        float posMult = 1;

        if (localPos.x <= -box.extendX)
        {
            posMult = -1;
        }

        quadX.ref.origin = quadX.ref.origin + quadX.ref.k * (posMult) * (box.extendZ + sphere.ray);

        if (IsSegmentIntersectionQuad(segment, quadX, hit))
        {
            return true;
        }
        
        Capsule tempCap = capY;
        tempCap.point = tempCap.point + (box.ref.i * (posMult * box.extendX) + box.ref.k * box.extendZ);

        if (IsSegmentIntersectingCapsule(segment, tempCap, hit))
        {
            return true;
        }

        tempCap.point = tempCap.point - (box.ref.i * (box.extendX * 2));
        
        if (IsSegmentIntersectingCapsule(segment, tempCap, hit))
        {
            return true;
        }

        tempCap = capZ;
        tempCap.point = tempCap.point + (box.ref.i * (posMult * box.extendX) + box.ref.j * box.extendY);
        if (IsSegmentIntersectingCapsule(segment, tempCap, hit))
        {
            return true;
        }

        tempCap.point = tempCap.point - (box.ref.i * (box.extendX * 2));
        
        if (IsSegmentIntersectingCapsule(segment, tempCap, hit))
        {
            return true;
        }
    }

    // check Z faces

    if (abs(localPos.z) >= box.extendZ)
    {
        float posMult = 1;

        if (localPos.z <= -box.extendZ)
        {
            posMult = -1;
        }

        quadZ.ref.origin = quadZ.ref.origin + quadZ.ref.k * (posMult) * (box.extendX + sphere.ray);

        if (IsSegmentIntersectionQuad(segment, quadZ, hit))
        {
            return true;
        }
        
        Capsule tempCap = capY;
        tempCap.point = tempCap.point + (box.ref.k * (posMult * box.extendZ) + box.ref.i * box.extendX);

        if (IsSegmentIntersectingCapsule(segment, tempCap, hit))
        {
            return true;
        }

        tempCap.point = tempCap.point - (box.ref.k * (box.extendZ * 2));
        
        if (IsSegmentIntersectingCapsule(segment, tempCap, hit))
        {
            return true;
        }

        tempCap = capX;
        tempCap.point = tempCap.point + (box.ref.k * (posMult * box.extendX) + box.ref.j * box.extendY);
        if (IsSegmentIntersectingCapsule(segment, tempCap, hit))
        {
            return true;
        }

        tempCap.point = tempCap.point - (box.ref.k * (box.extendX * 2));
        
        if (IsSegmentIntersectingCapsule(segment, tempCap, hit))
        {
            return true;
        }
    }

    return false;
}


float Collider::DistanceFromPointToSegment(Core::Maths::Vec3 point, Segment seg)
{
    float t = DotProduct(point - seg.A, seg.GetVector()) / (seg.GetVector()).GetSqrMagnitude(); // othogonal projection of point on segment with the equation P = seg.A + (seg.B - seg.A) * t

    t = std::min(std::max(0.f, t), 1.0f); // Set the projection on the closest point if it's outside of the segment

    Vec3 cPoint = seg.A + (seg.GetVector()) * t; // Get the closest point on segment

    return (point - cPoint).GetMagnitude();
}

float Collider::DistanceSqrFromPointToSegment(Core::Maths::Vec3 point, Segment seg)
{

    float t = DotProduct(point - seg.A, seg.GetVector()) / (seg.GetVector()).GetSqrMagnitude(); // othogonal projection of point on segment with the equation P = seg.A + (seg.B - seg.A) * t

    t = std::min(std::max(0.f, t), 1.0f); // Set the projection on the closest point if it's outside of the segment

    Vec3 cPoint = seg.A + (seg.GetVector()) * t; // Get the closest point on segment

    return (point - cPoint).GetSqrMagnitude();
}

Vec3 Collider::ClosestPointToSegment(Core::Maths::Vec3 point, Segment seg)
{

    float t = DotProduct(point - seg.A, seg.GetVector()) / (seg.GetVector()).GetSqrMagnitude(); // othogonal projection of point on segment with the equation P = seg.A + (seg.B - seg.A) * t

    t = std::min(std::max(0.f, t), 1.0f); // Set the projection on the closest point if it's outside

    Vec3 cPoint = seg.A + (seg.GetVector()) * t; // Get the closest point on segment

    return cPoint;
}

Vec3 Collider::ClosestPointToLine(Core::Maths::Vec3 point, Line line)
{
    float directionPower = DotProduct(line.direction, point - line.point);

    return (line.point + line.direction.Normalize() * directionPower);
}





bool Collider::IsOrientedBoxCollidingWithOrientedBox(Core::Maths::OrientedBox &box1, Core::Maths::OrientedBox &box2)
{
    std::vector<Vec3> listAxes = GetSATaxesBetweenTwoOrientedBoxes(box1, box2);

    std::vector<Vec3> box1Points = box1.GetWorldPoints();
    std::vector<Vec3> box2Points = box2.GetWorldPoints();

    for (unsigned int i = 0; i < listAxes.size(); ++i)
    {
        Range rangeSATbox1 = GetSATrange(listAxes[i], box1Points);
        Range rangeSATbox2 = GetSATrange(listAxes[i], box2Points);

        if (Range::IsRangesInterfere(rangeSATbox1, rangeSATbox2))
            return false;
    }

    return true;
}

std::vector<Vec3> Collider::GetSATaxesBetweenTwoOrientedBoxes(const Core::Maths::OrientedBox &box1, const Core::Maths::OrientedBox &box2)
{
    Referential ref1 = box1.ref;
    Referential ref2 = box2.ref;

    std::vector<Vec3> listSATaxes;

    listSATaxes.push_back(ref1.i);
    listSATaxes.push_back(ref1.j);
    listSATaxes.push_back(ref1.k);
    listSATaxes.push_back(ref2.i);
    listSATaxes.push_back(ref2.j);
    listSATaxes.push_back(ref2.k);
    listSATaxes.push_back(CrossProduct(ref1.i, ref2.i));
    listSATaxes.push_back(CrossProduct(ref1.i, ref2.j));
    listSATaxes.push_back(CrossProduct(ref1.i, ref2.k));
    listSATaxes.push_back(CrossProduct(ref1.j, ref2.i));
    listSATaxes.push_back(CrossProduct(ref1.j, ref2.j));
    listSATaxes.push_back(CrossProduct(ref1.j, ref2.k));
    listSATaxes.push_back(CrossProduct(ref1.k, ref2.i));
    listSATaxes.push_back(CrossProduct(ref1.k, ref2.j));
    listSATaxes.push_back(CrossProduct(ref1.k, ref2.k));

    return listSATaxes;
}

Range Collider::GetSATrange(const Vec3 &axis, const std::vector<Vec3> &points)
{
    Range range;

    for (unsigned int i = 0; i < points.size(); ++i)
    {
        range.AddValue(DotProduct(axis, points[i]));
    }

    return range;
}

bool Collider::IsOrientedBoxAndPointCollide(OrientedBox box, Vec3 pt)
{
    box.ref.origin = box.position;
    Vec3 localPos = box.ref.Point_World_To_Local(pt);

    if (Abs(localPos.x) > box.extendX || Abs(localPos.y) > box.extendY || Abs(localPos.z) > box.extendZ)
        return false;

    return true;
}

/*
bool Collider::IsSegmentAndAABBCollide(Segment seg, AABB aabb, Hit &hit)
{
    aabb.ref.origin = aabb.center;
    Vec3 localPosA = aabb.ref.Point_World_To_Local(seg.A);
    Vec3 localPosB = aabb.ref.Point_World_To_Local(seg.B);
    // check if point A & B is in the same side
    if (((localPosA.x && localPosB.x) > aabb.extendX || (localPosA.x && localPosB.x) < -aabb.extendX) ||
        ((localPosA.y && localPosB.y) > aabb.extendY || (localPosA.y && localPosB.y) < -aabb.extendY) ||
        ((localPosA.z && localPosB.z) > aabb.extendZ || (localPosA.z && localPosB.z) < -aabb.extendZ))
        return false;

    Segment localSegment(localPosA, localPosB);

    bool test = false;
    if (localPosA.x >= aabb.extendX) // right face
    {
        std::cout << "rightFace" << std::endl;
        Plane rightFace(aabb.ref.i, aabb.extendX);
        test = IsSegmentAndPlaneCollide(localSegment, rightFace, hit);
    }
    else if (localPosA.x <= -aabb.extendX) // left face
    {
        std::cout << "leftFace" << std::endl;
        Plane leftFace(aabb.ref.i * -1, aabb.extendX);
        test = IsSegmentAndPlaneCollide(localSegment, leftFace, hit);
    }
    else if (localPosA.y >= aabb.extendY) // top face
    {
        std::cout << "topFace" << std::endl;
        Plane topFace(aabb.ref.j, aabb.extendY);
        test = IsSegmentAndPlaneCollide(localSegment, topFace, hit);
    }
    else if (localPosA.y <= -aabb.extendY) // bottom face
    {
        std::cout << "bottomFace" << std::endl;
        Plane downFace(aabb.ref.j * -1, aabb.extendY);
        test = IsSegmentAndPlaneCollide(localSegment, downFace, hit);
    }
    else if (localPosA.z >= aabb.extendZ) // front face
    {
        std::cout << "frontFace" << std::endl;
        Plane frontFace(aabb.ref.k, aabb.extendZ);
        test = IsSegmentAndPlaneCollide(localSegment, frontFace, hit);
    }
    else if (localPosA.z <= -aabb.extendZ) // back face
    {
        std::cout << "backFace" << std::endl;
        Plane backFace(aabb.ref.k * -1, aabb.extendZ);
        test = IsSegmentAndPlaneCollide(localSegment, backFace, hit);
    }

    if (test)
    {
        hit.point = hit.point + aabb.center;
        return true;
    }
    else
        return false;
}*/

/*bool Collider::IsSegmentAndOrientedBoxCollide(Segment seg, OrientedBox box, Hit &hit)
{
    if (Collider::IsOrientedBoxAndPointCollide(box, seg.A) || Collider::IsOrientedBoxAndPointCollide(box, seg.B))
        return true;

    box.ref.origin = box.position;
    Vec3 localPosA = box.ref.Point_World_To_Local(seg.A);
    Vec3 localPosB = box.ref.Point_World_To_Local(seg.B);

    if (((localPosA.x && localPosB.x) > box.extendX || (localPosA.x && localPosB.x) < -box.extendX) &&
        ((localPosA.y && localPosB.y) > box.extendY || (localPosA.y && localPosB.y) < -box.extendY) &&
        ((localPosA.z && localPosB.z) > box.extendZ || (localPosA.z && localPosB.z) < -box.extendZ))
        return false;

    Segment localSegment(localPosA, localPosB);

    bool test = false;
    if (localPosA.x >= box.extendX) // right face
    {
        std::cout << "rightFace" << std::endl;
        Plane rightFace(box.ref.i, box.extendX);
        test = IsSegmentAndPlaneCollide(localSegment, rightFace, hit);
    }
    else if (localPosA.x <= -box.extendX) // left face
    {
        std::cout << "leftFace" << std::endl;
        Plane leftFace(box.ref.i * -1, box.extendX);
        test = IsSegmentAndPlaneCollide(localSegment, leftFace, hit);
    }
    else if (localPosA.y >= box.extendY) // top face
    {
        std::cout << "topFace" << std::endl;
        Plane topFace(box.ref.j, box.extendY);
        test = IsSegmentAndPlaneCollide(localSegment, topFace, hit);
    }
    else if (localPosA.y <= -box.extendY) // bottom face
    {
        std::cout << "bottomFace" << std::endl;
        Plane downFace(box.ref.j * -1, box.extendY);
        test = IsSegmentAndPlaneCollide(localSegment, downFace, hit);
    }
    else if (localPosA.z >= box.extendZ) // front face
    {
        std::cout << "frontFace" << std::endl;
        Plane frontFace(box.ref.k, box.extendZ);
        test = IsSegmentAndPlaneCollide(localSegment, frontFace, hit);
    }
    else if (localPosA.z <= -box.extendZ) // back face
    {
        std::cout << "backFace" << std::endl;
        Plane backFace(box.ref.k * -1, box.extendZ);
        test = IsSegmentAndPlaneCollide(localSegment, backFace, hit);
    }

    if (test)
    {
        hit.point = hit.point + box.position;
        return true;
    }
    else
        return false;
}*/