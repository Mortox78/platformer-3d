#ifndef _CAMERA_
#define _CAMERA_

#include "matrix.hpp"

#define ORTHO 180
#define FORWARD  1.f
#define BACK    -1.f
#define RIGHT    2.f
#define LEFT     -2.f    

using namespace Core;

#include <iostream>

namespace LowRenderer
{
    class Camera
    {
    public:
        Maths::Vec3 position {0,0,1};
        Maths::Vec3 aim;
        Maths::Vec3 Z        {0,1,0};

        float fov = ORTHO;

        float width {1};
        float height {1};

        float near {0.01};
        float far  {1};

        float yaw {0};
        float pitch {0};
        bool  firstPerson {false};

        Camera(){};
        Camera(float fov, float _width, float _height, float _near, float _far);
        ~Camera();

        Maths::Mat4 GetMatrixPerspective()    const;
        Maths::Mat4 GetMatrixTransformation() const;
    
        void SetLookAt(Maths::Vec3 _aim, Maths::Vec3 _position, Maths::Vec3 _Z); // Set the element use to create the lookAt matrix of the camera

        bool FirstPersonMove(float direction, float distance); // move on the XZ plane
    };
}

#endif