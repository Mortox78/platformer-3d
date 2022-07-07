#include "SphereCollider.hpp"

using namespace Physics;

SphereCollider::SphereCollider()
{
    type = ColliderType::SPHERE;
    sphere.ray = 1;
}

Sphere SphereCollider::GetSphere()
{
    sphere.position = transform->position;
    return sphere;
}