#include "Line.hpp"

using namespace Core::Maths;

Line::Line(/* args */)
{
}

Line::Line(const Segment &seg)
{
    point = seg.A;
    direction = (seg.B - seg.A).Normalize();
}

Line::Line(const Vec3 &_point, const Vec3 &_direction) : point{_point}, direction{_direction} {}

Line::~Line()
{
}