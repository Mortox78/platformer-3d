#include "Segment.hpp"

using namespace Core::Maths;

Segment::Segment(): A{Vec3(0,0,0)}, B{Vec3(0,0,0)}{}
Segment::Segment(Vec3 a, Vec3 b): A{a}, B{b}{}
Segment::~Segment(){}

Vec3 Segment::GetVector() const
{
    return (B - A);
}

Vec3 Segment::GetNormalizedVector() const
{
    return (B - A).Normalize();
}