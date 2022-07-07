#include "Assertion.hpp"

void Debug::Assertion::Check(unsigned int risk, bool check, const std::string &message)
{
    if (!check)
        return;
    if (risk == HIGH)
    {
        printf(RED);
        std::cout << "MAJOR ERROR : ";
        printf(RESET);
        std::cout << message << std::endl; 
        exit(0); // stop the program
    }
    
    if (risk == LOW)
    {
        printf(BOLD_GREEN);
        std::cout << "MINOR ERROR : ";
        printf(RESET);
        std::cout << message << std::endl;
    }
}

void Debug::Assertion::DebugLogTransform(std::string name, Physics::Transform transform, float range)
{
    std::cout << name << ":" << std::endl;
    std::cout << "Position(" << transform.position.x << ", " << transform.position.y << ", " << transform.position.z << ")" << std::endl;
    std::cout << "Rotation(" << transform.rotation.x << ", " << transform.rotation.y << ", " << transform.rotation.z << ")" << std::endl;
    std::cout << "Scale(" << transform.scale.x << ", " << transform.scale.y << ", " << transform.scale.z << ")" << std::endl;
    std::cout << "Range = " << range << "\n"
              << std::endl;
}
void Debug::Assertion::DebugLogVec3(std::string name, Core::Maths::Vec3 v)
{
    std::cout << name << ":" << std::endl;
    std::cout << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
}