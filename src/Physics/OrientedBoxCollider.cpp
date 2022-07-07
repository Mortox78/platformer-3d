#include "OrientedBoxCollider.hpp"

using namespace Physics;

OrientedBoxCollider::OrientedBoxCollider()
{
    type = ColliderType::ORIENTED_BOX;
}

OrientedBox OrientedBoxCollider::GetOrientedBox()
{

    orientedBox.extendX = transform->scale.x / 2;
    orientedBox.extendY = transform->scale.y / 2;
    orientedBox.extendZ = transform->scale.z / 2;

    orientedBox.ref.origin = transform->position;

    Vec4 i = transform->getMatrix() * Vec4(orientedBox.ref.i, 0);
    Vec4 j = transform->getMatrix() * Vec4(orientedBox.ref.j, 0);
    Vec4 k = transform->getMatrix() * Vec4(orientedBox.ref.k, 0);

    orientedBox.ref.i = Vec3{i.x, i.y, i.z}.Normalize();
    orientedBox.ref.j = Vec3{j.x, j.y, j.z}.Normalize();
    orientedBox.ref.k = Vec3{k.x, k.y, k.z}.Normalize();

    orientedBox.position = transform->position;
    return orientedBox;
}