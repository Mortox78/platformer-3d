#pragma once

#include "vector3D.hpp"

namespace Core::Maths
{
    class Segment
    {
    public:
        Vec3 A;
        Vec3 B;

        Segment();
        Segment(Vec3 a, Vec3 b);
        ~Segment();

        Vec3 GetVector() const;
        Vec3 GetNormalizedVector() const;
    };
}