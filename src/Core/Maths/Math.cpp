#include "Math.hpp"

#define EPSILON 0.01f

float Core::Maths::Abs(float value)
{
    return value < 0? value * -1: value;
}

float Core::Maths::Clamp(float value, float low, float high)
{
    if(low > high)
    {
        float temp = low;
        low = high;
        high = temp;
    }
    
    return (value < low) ? low : (high < value) ? high : value;
}

bool Core::Maths::testWithEpsilon(float value, float valueToCompare)
{
    return (value < valueToCompare - EPSILON) ? false : (value > valueToCompare + EPSILON)? false : true;
}