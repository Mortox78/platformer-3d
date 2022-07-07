#include "vector2D.hpp"

using namespace Core::Maths;

Vec2::Vec2()
{
}

Vec2::Vec2(float _x, float _y)
{
    x = _x;
    y = _y;
}

Vec2::~Vec2()
{
}

float Vec2::GetMagnitude() const
{
    return sqrt((x * x) + (y * y));
}

Vec2& Vec2::Normalize()
{
    float length = GetMagnitude();

    x /= length;
    y /= length;

    return *this;
}

Vec2 Vec2::Normalize() const
{
    float length = GetMagnitude();

    float x = this->x / length;
    float y = this->y / length;

    return {x,y};
}

Vec2 operator+(const Vec2 &vect1, const Vec2 &vect2)
{
    Vec2 result;

    result.x = vect1.x + vect2.x;
    result.y = vect1.y + vect2.y;

    return result;
}

Vec2 operator-(const Vec2 &vect1, const Vec2 &vect2)
{
    Vec2 result;

    result.x = vect1.x - vect2.x;
    result.y = vect1.y - vect2.y;

    return result;
}

Vec2 operator*(const Vec2 &vect, float scale)
{
    Vec2 result;

    result.x = vect.x * scale;
    result.y = vect.y * scale;

    return result;
}

float operator*(const Vec2& v1, const Vec2& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}
