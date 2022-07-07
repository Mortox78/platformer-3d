#ifndef _VERTEX_
#define _VERTEX_

#include "vector2D.hpp"
#include "vector3D.hpp"
#include "vector4D.hpp"


struct Vertex
{
    Core::Maths::Vec3     position    {0,0,0};
    Core::Maths::Vec3     normal      {0,0,0};
    Core::Maths::Vec2     texture     {0,0};
    Core::Maths::Vec4     color       {1,1,1,1};
};



#endif
