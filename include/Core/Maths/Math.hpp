#pragma once

namespace Core
{
    namespace Maths
    {
        float Abs(float value);
        float Clamp(float value, float low, float high);
        bool testWithEpsilon(float value, float valueToCompare);
    }
}