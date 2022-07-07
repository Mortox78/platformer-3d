#include "Transform.hpp"

Physics::Transform::Transform(){}
Physics::Transform::Transform(const Core::Maths::Vec3 &_position, const Core::Maths::Vec3 &_scale, const Core::Maths::Vec3 &_rotation)
{
    position    = _position;
    scale       = _scale;
    rotation    = _rotation;
}
Physics::Transform::~Transform(){}
Core::Maths::Mat4 Physics::Transform::getMatrix()
{
    return Core::Maths::Mat4::CreateTransformMatrix(rotation, position, scale);
}