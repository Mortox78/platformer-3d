#include "Camera.hpp"

using namespace LowRenderer;

Camera::Camera(float _fov, float _width, float _height, float _near, float _far)
{
    fov     = _fov;
    width   = _width;
    height  = _height;
    near    = _near;
    far     = _far;
}

Camera::~Camera()
{
}

void Camera::SetLookAt(Maths::Vec3 _aim, Maths::Vec3 _position, Maths::Vec3 _Z) // matrix use for the camera
{
    aim         = _aim;
    position    = _position;
    Z           = _Z;
}

Maths::Mat4 Camera::GetMatrixPerspective() const
{

    if (fov == ORTHO || ((int)fov % ORTHO) == 0)
    {
        return Maths::Mat4::CreateOrthographicMatrix(width, height, near, far);
    }
    else
        return Maths::Mat4::CreatePerspectiveProjectionMatrix(width, height, near, far, fov);
}

Maths::Mat4 Camera::GetMatrixTransformation() const
{
    if (!firstPerson)
    {
        return Maths::Mat4::CreateCameraMatrix(aim, position, Z);
    }
    else
    {
        return Maths::Mat4::CreateXRotationMatrix(pitch)
             * Maths::Mat4::CreateYRotationMatrix(yaw) 
             * Maths::Mat4::CreateTranslationMatrix(position * (-1));
    }
}

bool Camera::FirstPersonMove(float direction, float distance)
{
    if (!firstPerson)
        return false;

    Maths::Vec3 aimPoint;
    aimPoint.x = sinf(yaw) * cosf(pitch);
    aimPoint.y = sinf(yaw) * sinf(pitch);
    aimPoint.z = -cosf(yaw);
    Maths::Vec3 mouvement = aimPoint.Normalize();

    if (direction == FORWARD)
    {
        position.x += mouvement.x * distance;
        position.z += mouvement.z * distance;
    }
    
    else if (direction == BACK)
    {    
        position.x -= mouvement.x * distance;
        position.z -= mouvement.z * distance;
    }

    else if (direction == RIGHT)
    {
        position.x += (mouvement.x * cosf(PI / 2) - mouvement.z * sinf(PI / 2)) * distance;
        position.z += (mouvement.x * sinf(PI / 2) + mouvement.z * cosf(PI / 2)) * distance;
    }
    else if (direction == LEFT)
    {
        position.x -= (mouvement.x * cosf(PI / 2) - mouvement.z * sinf(PI / 2)) * distance;
        position.z -= (mouvement.x * sinf(PI / 2) + mouvement.z * cosf(PI / 2)) * distance;
    }

    return true;

}