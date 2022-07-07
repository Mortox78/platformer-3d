#ifndef _VECTOR2D_
#define _VECTOR2D_

#include <cmath>
namespace Core
{
    namespace Maths
    {
        class Vec2
        {
        public:
            float x{0};
            float y{0};
        
            Vec2    ();
            Vec2    (float _x, float _y);
            ~Vec2   ();
        
            float   GetMagnitude    () const;
            Vec2    &Normalize      ();
            Vec2    Normalize       () const;
        };
    }
} // namespace Core
Core::Maths::Vec2   operator+   (const Core::Maths::Vec2 &, const Core::Maths::Vec2 &);
Core::Maths::Vec2   operator-   (const Core::Maths::Vec2 &vect1, const Core::Maths::Vec2 &vect2);
Core::Maths::Vec2   operator*   (const Core::Maths::Vec2 &, float);
float               operator*   (const Core::Maths::Vec2 &, const Core::Maths::Vec2 &);

#endif