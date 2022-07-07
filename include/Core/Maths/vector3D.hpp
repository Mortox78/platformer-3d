#ifndef _VECTOR3D_
#define _VECTOR3D_

#include <cmath>
#include <iostream>

namespace Core
{
    namespace Maths
    {
        class Vec3
        {
        public:
            float x{0};
            float y{0};
            float z{0};
        
            Vec3    ();
            Vec3    (float _x, float _y, float _z);
            ~Vec3   ();
        
            float   GetMagnitude    () const;
            float   GetSqrMagnitude () const;
            Vec3    &Normalize      ();
            Vec3    Normalize       () const;

            static float AngleBetweenVector(const Vec3 &vect1, const Vec3 &vect2);

            friend std::ostream& operator<<(std::ostream& os, const Vec3& vec)
            {
                os << vec.x << std::endl;
                os << vec.y << std::endl;
                os << vec.z << std::endl;
            
                return os;
            }

            friend std::istream& operator>>(std::istream& is, Vec3& vec)
            {
                is >> vec.x;
                is >> vec.y;
                is >> vec.z;
            
                return is;
            }
        };
    }
} // namespace Core



Core::Maths::Vec3   operator+   (const Core::Maths::Vec3 &, const Core::Maths::Vec3 &);
Core::Maths::Vec3   operator-   (const Core::Maths::Vec3 &, const Core::Maths::Vec3 &);
Core::Maths::Vec3   operator*   (const Core::Maths::Vec3 &, float);
float               operator*   (const Core::Maths::Vec3 &, const Core::Maths::Vec3 &);
bool                operator==  (const Core::Maths::Vec3 &, const Core::Maths::Vec3 &);

float               DotProduct  (const Core::Maths::Vec3& v1, const Core::Maths::Vec3& v2);
Core::Maths::Vec3   CrossProduct(const Core::Maths::Vec3 &v1, const Core::Maths::Vec3 &v2);

#endif