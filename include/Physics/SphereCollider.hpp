#pragma once
#include "Collider.hpp"

namespace Physics
{
    class SphereCollider : public Physics::Collider
    {
        private:
            float ray {1};
        
            Sphere sphere;

        public:

            SphereCollider();
            ~SphereCollider(){};

            Sphere GetSphere();
    };
}