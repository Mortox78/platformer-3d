#pragma once

#include "referential.hpp"

namespace Core
{
    namespace Maths
    {
        class Quad
        {
            public:
                Quad(const Vec3& _pos, const Referential& _ref, const float& _extendX, const float& _extendY);
                Quad(const Referential& _ref, const float& _extendX, const float& _extendY) : ref{_ref}, extendX{_extendX}, extendY{_extendY} {};
                Quad(){}
                ~Quad(){}

                Vec3 pos;
                Referential ref;
                float extendX = 1.f, extendY = 1.f;
        };
    }
}