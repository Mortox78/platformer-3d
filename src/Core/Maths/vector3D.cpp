#include "vector3D.hpp"

using namespace Core::Maths;

Vec3::Vec3(): x{0}, y{0}, z{0}{}

Vec3::Vec3(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
}

Vec3::~Vec3()
{
}

float Vec3::GetMagnitude() const
{
    return sqrt((x * x) + (y * y) + (z * z));
}

float Vec3::GetSqrMagnitude() const
{
    return (x * x) + (y * y) + (z * z);
}

Vec3& Vec3::Normalize()
{
    float length = GetMagnitude();

    x /= length;
    y /= length;
    z /= length;

    return *this;
}

Vec3 Vec3::Normalize() const
{
    float length = GetMagnitude();

    float x = this->x / length;
    float y = this->y / length;
    float z = this->z / length;

    return {x,y,z};
}

float Vec3::AngleBetweenVector(const Vec3 &vect1, const Vec3 &vect2)
{
    float angle = acos((DotProduct(vect1, vect2)) / (vect1.GetMagnitude() * vect2.GetMagnitude()));
    return angle;
}

Vec3 operator+(const Vec3 &vect1, const Vec3 &vect2)
{
    Vec3 result;

    result.x = vect1.x + vect2.x;
    result.y = vect1.y + vect2.y;
    result.z = vect1.z + vect2.z;

    return result;
}

Vec3 operator-(const Vec3 &vect1, const Vec3 &vect2)
{
    Vec3 result;

    result.x = vect1.x - vect2.x;
    result.y = vect1.y - vect2.y;
    result.z = vect1.z - vect2.z;

    return result;
}

Vec3 operator*(const Vec3 &vect, float scale)
{
    Vec3 result;

    result.x = vect.x * scale;
    result.y = vect.y * scale;
    result.z = vect.z * scale;

    return result;
}

float operator*(const Vec3& v1, const Vec3& v2)
{
    return v1.x * v2.x + v1.y * v2.y  + v1.z * v2.z;
}

float DotProduct(const Vec3& v1, const Vec3& v2)
{
    return v1.x * v2.x + v1.y * v2.y  + v1.z * v2.z;
}

Vec3 CrossProduct(const Vec3& v1, const Vec3& v2)
{
    Vec3 result;

    result.x = (v1.y * v2.z) - (v1.z * v2.y);
    result.y = (v1.z * v2.x) - (v1.x * v2.z);
    result.z = (v1.x * v2.y) - (v1.y * v2.x);

    return result;
}

bool operator==(const Vec3& v1, const Vec3& v2)
{
    return ((v1 - v2).GetSqrMagnitude() == 0);
}