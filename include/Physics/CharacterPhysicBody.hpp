#ifndef _CHARACTERPHYSICSBODY_
#define _CHARACTERPHYSICSBODY_

#include "SphereCollider.hpp"
#include "AdditionalBehavior.hpp"

#define CHARACTER_PHYSIC_BODY "CharacterPhysicBody"

namespace Physics
{
    class CharacterPhysicBody : public Physics::Collider
    {
    private:

    public:

        Physics::SphereCollider collider;
        Vec3 velocity;

        float gravity = 0.1;
        float jump = 10;

        Vec3 SpeedLimit{1,1,1};

        bool isGrounded = false;

        CharacterPhysicBody();
        ~CharacterPhysicBody();

        void Start(Physics::Transform* trs) override;
        void Update() override;
        
        void AddForce(const Vec3& force);

        void Move(float deltaTime);
        void ApplyLimit();
    };
}

#endif