#include "Sphere.hpp"

using namespace Core::Maths;

Sphere::Sphere() : ray{1} {}
Sphere::Sphere(Vec3 _position, float _ray) : position{_position}, ray{_ray} {}
Sphere::~Sphere() {}