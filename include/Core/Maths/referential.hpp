#pragma once
#include "vector3D.hpp"

namespace Core
{
    namespace Maths
    {
        class Referential
        {
            public:
                Vec3 i {1,0,0};
                Vec3 j {0,1,0};
                Vec3 k {0,0,1};

                Vec3 origin;
                //Vec3 position;
                
                Referential();
                Referential(Vec3 _i, Vec3 _j, Vec3 _k, Vec3 _position);
                ~Referential();

                Vec3 Point_Local_To_World(Vec3 point) const;
                Vec3 Point_World_To_Local(Vec3 point) const;
                Vec3 Vector_Local_To_World(Vec3 vec) const;
                Vec3 Vector_World_To_Local(Vec3 vec) const;


                Vec3 PointLocalToWorld(Vec3 point) const;
                Vec3 PointWorldToLocal(Vec3 point) const;
                Vec3 VectorLocalToWorld(Vec3 vec) const;
                Vec3 VectorWorldToLocal(Vec3 vec) const;

                friend std::ostream& operator<<(std::ostream& os, const Referential& ref)
                {
                    os << ref.i;
                    os << ref.j;
                    os << ref.k;

                    return os;
                }

                friend std::istream& operator>>(std::istream& is, Referential& ref)
                {
                    is >> ref.i;
                    is >> ref.j;
                    is >> ref.k;

                    return is;
                }
        };
    }
}