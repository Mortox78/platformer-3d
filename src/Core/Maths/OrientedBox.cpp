#include <iostream>
#include <vector>

#include "OrientedBox.hpp"

using namespace Core::Maths;

OrientedBox::OrientedBox() {}
OrientedBox::OrientedBox(Referential _ref, Vec3 _position, float _extend) : position{_position}, extendX{_extend}, extendY{_extend}, extendZ{_extend}, ref{_ref} 
{
    //ref.position = position;
}
OrientedBox::~OrientedBox() {}

std::vector<Vec3> OrientedBox::GetWorldPoints()
{
    std::vector<Vec3> points;

    points.push_back(position + ref.i * extendX + ref.j * extendY + ref.k * extendZ);
    points.push_back(position + ref.i * -extendX + ref.j * extendY + ref.k * extendZ);
    points.push_back(position + ref.i * extendX + ref.j * -extendY + ref.k * extendZ);
    points.push_back(position + ref.i * extendX + ref.j * extendY + ref.k * -extendZ);
    points.push_back(position + ref.i * -extendX + ref.j * -extendY + ref.k * extendZ);
    points.push_back(position + ref.i * extendX + ref.j * -extendY + ref.k * -extendZ);
    points.push_back(position + ref.i * -extendX + ref.j * extendY + ref.k * -extendZ);
    points.push_back(position + ref.i * -extendX + ref.j * -extendY + ref.k * -extendZ);

    return points;
}