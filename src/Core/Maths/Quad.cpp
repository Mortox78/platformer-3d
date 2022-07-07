#include <iostream>

#include "Quad.hpp"

using namespace Core::Maths;

Quad::Quad(const Vec3& _pos, const Referential& _ref, const float& _extendX, const float& _extendY)
{
    pos = _pos;
    ref = _ref;
    extendX = _extendX;
    extendY = _extendY;
}