#pragma once

#include <iostream>
#include <vector>

#include "Transform.hpp"
#include "Sphere.hpp"
#include "Cylinder.hpp"
#include "OrientedBox.hpp"
#include "Segment.hpp"
#include "Plane.hpp"
#include "AABB.hpp"
#include "Quad.hpp"
#include "Range.hpp"

#include "Hit.hpp"

#include "AdditionalBehavior.hpp"

namespace Physics
{
    enum ColliderType
    {
        SPHERE,
        ORIENTED_BOX,
        SEGMENT,
        COLLIDER
    };

    class Collider : public Core::DataStructure::AdditionalBehavior
    {
        protected:
            ColliderType type;
            
            static std::vector<Collider*> allCollider;

        public:
            Collider();
            ~Collider(){};

            void Start(Physics::Transform* trs) override;
            void Update() override{};

            ColliderType Type() const;

            // Collision Oriented Box and Oriented Box
            static bool IsOrientedBoxCollidingWithOrientedBox(Core::Maths::OrientedBox& box1, Core::Maths::OrientedBox& box2);
            static std::vector<Vec3> GetSATaxesBetweenTwoOrientedBoxes(const Core::Maths::OrientedBox& box1, const Core::Maths::OrientedBox& box2);
            static Range GetSATrange(const Vec3& axis, const std::vector<Vec3>& points);
            // Collision segment and sphere
            //

            static bool CheckCollisionWithAllCollider(Collider* collider);
            static bool SimpleCheckCollide(const Collider* collider1, const Collider* collider2, bool AABBCheck = false);
            
            /*******************************Segment(start)*******************************/
            static bool IsSegmentAndPlaneCollide(const Segment &seg, const Plane &plane, Hit &hit);
            static bool IsSegmentIntersectionQuad(const Segment& segment, Quad& quad, Hit& hit);
            static bool IsSegmentIntersectingSphere(const Segment& segment, const Sphere& sphere, Hit& hit);
            static bool IsSegmentIntersectingInfiniteCylinder(const Segment &seg, const InfiniteCylinder &cylinder, Hit &hit);
            static bool IsSegmentIntersectingCylinder(const Segment &seg, const Cylinder &cylinder, Hit &hit);
            static bool IsSegmentIntersectingCapsule(const Segment &seg, const Capsule &capsule, Hit &hit);

            static bool IsSegmentAndAABBCollide(const Segment &seg, const AABB &aabb, Hit &hit);
            static bool IsSegmentAndOrientedBoxCollide(const Segment &seg, const OrientedBox &box, Hit &hit);
            /********************************Segment(end)********************************/

            static bool IsSphereAndOrientedBoxCollide(Sphere sphere, OrientedBox box);
            static bool IsOrientedBoxAndPointCollide(OrientedBox box, Vec3 pt);

            static bool GetFirstCollisionPointBetweenMovingSphereAndStaticBox(const OrientedBox& box, const Sphere &sphere, const Vec3 &seg, float deltaTime, Hit &hit);


            static float DistanceFromPointToSegment(Core::Maths::Vec3 point, Segment seg);
            static float DistanceSqrFromPointToSegment(Core::Maths::Vec3 point, Segment seg);
            static Vec3 ClosestPointToSegment(Core::Maths::Vec3 point, Segment seg);
            static Vec3 ClosestPointToLine(Core::Maths::Vec3 point, Line line);
    };
} // namespace Physics
