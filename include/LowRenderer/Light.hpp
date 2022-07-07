#ifndef _LIGHT_
#define _LIGHT_

#include "vector3D.hpp"
#include "Vertex.hpp"

namespace LowRenderer
{
    class Light
    {
    public:
        Core::Maths::Vec3 position  {0,0,0}; // use for point and spot light

        Core::Maths::Vec3 direction {0,0,0}; // use for directional and spot light
                                             // if direction isn't set the light will be a point light
        
        Core::Maths::Vec3 ambient   {0,0,0}; // colors of the lights
        Core::Maths::Vec3 diffuse   {0,0,0};
        Core::Maths::Vec3 specular  {0,0,0};

        float constant              {1.0f}; // use for attenuation
        float linear                {0.0f};
        float quadratic             {0.0f};
        
        float spotAngle             {0.0f}; // angle of the spot
                                            // if the angle isn't set the light will be directional if direction is set

        Light(){};
        ~Light(){}
    };
}

#endif