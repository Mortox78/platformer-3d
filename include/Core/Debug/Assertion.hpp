#ifndef _ASSERTION_
#define _ASSERTION_

#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BOLD_GREEN "\033[1;32m"
#define RESET "\033[0m"

#define LOW 0
#define HIGH 1

#include <iostream>
#include <string>

#include <stdio.h> 
#include <stdlib.h>

#include "vector3D.hpp"
#include "Transform.hpp"

namespace Debug
{
    namespace Assertion
    {
        void Check(unsigned int risk, bool check, const std::string &message);
        // risk determine if the pragrom must be stop or not
        // check dertemine the error
        // "message" is is display on the the terminal if there is an error

        void DebugLogTransform(std::string name, Physics::Transform transform, float range);
        void DebugLogVec3(std::string name, Core::Maths::Vec3 v);
    }
}

#endif