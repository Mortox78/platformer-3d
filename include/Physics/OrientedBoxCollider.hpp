#pragma once
#include "Collider.hpp"

namespace Physics
{
    class OrientedBoxCollider : public Physics::Collider
    {
        private:
            OrientedBox orientedBox;
                    
        public:
            OrientedBoxCollider();
            ~OrientedBoxCollider(){};

            OrientedBox GetOrientedBox();
    };
}