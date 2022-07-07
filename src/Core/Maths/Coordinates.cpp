#include "Coordinates.hpp"

using namespace Core::Maths;
using namespace Coordinates;

Cylindical::Cylindical(float _r, float _theta, float _z)
{
    r = _r;
    theta = _theta;
    z = _z;
}

Cylindical::Cylindical(const Vec3 &vec)
{
    r = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    if (vec.y > 0)
        theta = acosf(vec.x / r);
    else
        theta = 2 * M_PI - acosf(vec.x / r);
    z = vec.z;
}

Vec3 Cylindical::convertToCartesien()
{
    Vec3 vec;

    vec.x = r * cosf(theta);
    vec.y = r * sinf(theta);
    vec.z = z;

    return vec;
}

void Cylindical::convertToCylincal(const Vec3 &vec)
{
    r = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    if (vec.y > 0)
        theta = acosf(vec.x / r);
    else
        theta = 2 * M_PI - acosf(vec.x / r);
    z = vec.z;
}

Spherical::Spherical(float _r, float _theta, float _phi)
{
    r = _r;
    theta = _theta;
    phi = _phi;
}

Spherical::Spherical(const Vec3 &vec)
{
    r = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    if (vec.y > 0)
        theta = acosf(vec.x / r);
    else
        theta = 2 * M_PI - acosf(vec.x / r);
    phi = acosf(vec.z / r);
}

Vec3 Spherical::convertToCartesien()
{
    Vec3 vec;

    vec.x = r * sinf(phi) * cosf(theta);
    vec.y = r * sinf(phi) * sinf(theta);
    vec.z = r * cosf(phi);

    return vec;
}

void Spherical::convertToSpherical(const Vec3 &vec)
{
    r = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    if (vec.y > 0)
        theta = acosf(vec.x / r);
    else
        theta = 2 * M_PI - acosf(vec.x / r);
    phi = acosf(vec.z / r);
}
