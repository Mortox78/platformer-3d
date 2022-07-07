#pragma once

#include <iostream>
#include <vector>

#include "Transform.hpp"

namespace Core
{
    namespace Maths
    {
        class OrientedBox
        {
            private:
            public:

                Referential ref;
                Vec3 position {0,0,0};
                Vec3 rotation {0,0,0};
                float extendX {0.5f};
                float extendY {0.5f};
                float extendZ {0.5f};

                OrientedBox();
                OrientedBox(Referential _ref, Vec3 _position, float _extend);
                ~OrientedBox();

                std::vector<Vec3> GetWorldPoints();
        };
    } // namespace Maths
} // namespace Core