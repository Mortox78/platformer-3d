#include <iostream>

#include "Range.hpp"

using namespace Core::Maths;

void Range::AddValue(const float& valueToAdd)
{
    if (min == 0.f && max == 0.f)
    {
        min = valueToAdd;
        max = valueToAdd;
    }
    else if (valueToAdd < min)
    {
        min = valueToAdd;
    }
    else if (valueToAdd > max)
    {
        max = valueToAdd;
    }
}

bool Range::IsRangesInterfere(const Range& range1, const Range& range2)
{
    if (range1.min < range2.max && range1.min > range2.min
    ||  range2.min < range1.max && range2.min > range1.min)
    {
        return true;
    }
    return false;
}