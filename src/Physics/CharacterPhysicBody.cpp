#include "CharacterPhysicBody.hpp"

#include "OrientedBoxCollider.hpp"

using namespace Physics;

CharacterPhysicBody::CharacterPhysicBody()
{
    name = CHARACTER_PHYSIC_BODY;
}

CharacterPhysicBody::~CharacterPhysicBody()
{
}

void CharacterPhysicBody::Start(Physics::Transform* trs)
{
    transform = trs;
    collider.transform = trs;
}

void CharacterPhysicBody::Update()
{
    Sphere sph = collider.GetSphere();

    Hit hit;

    if (isGrounded)
    {
        velocity.y = 0;
    }
    else
    {
        velocity.y -= gravity;
    }
    
    ApplyLimit();
    Move(1);
}

void CharacterPhysicBody::AddForce(const Vec3& force)
{
    velocity = velocity + force;   
}

void CharacterPhysicBody::Move(float deltaTime)
{
    isGrounded = false;

    Sphere sph = collider.GetSphere();
    sph.position = sph.position + velocity;

    unsigned int listSize = allCollider.size();
    for (unsigned int i = 0; i < listSize; i++)
    {
        if ((Collider*)(&collider) != allCollider[i])
        {
            if(allCollider[i]->Type() == ColliderType::ORIENTED_BOX)
            {                
                if (AABB::SphereAndOrientedBoxAABBCollision(sph, ((OrientedBoxCollider*)(allCollider[i]))->GetOrientedBox()))
                {
                    if (IsSphereAndOrientedBoxCollide(sph, ((OrientedBoxCollider*)(allCollider[i]))->GetOrientedBox()))
                    {
                        Hit hit;

                        Sphere sph = collider.GetSphere();
                        sph.position = sph.position + velocity;
                        if (GetFirstCollisionPointBetweenMovingSphereAndStaticBox(((OrientedBoxCollider*)(allCollider[i]))->GetOrientedBox(), collider.GetSphere(), velocity, deltaTime, hit))
                        {         
                            if (hit.normal.y > 0)
                            {
                                isGrounded = true;
                            }

                            hit.normal.Normalize();
                            velocity.x *= (1 - hit.normal.x);
                            velocity.y *= (1 - hit.normal.y);
                            velocity.z *= (1 - hit.normal.z);
                        }
                    }
                }
            }
                
        }
    }

    transform->position = transform->position + velocity;

}

void CharacterPhysicBody::ApplyLimit()
{
    if (abs(velocity.x) > SpeedLimit.x && velocity.x != 0)
    {
        velocity.x = SpeedLimit.x * (abs(velocity.x) / velocity.x);
    }
    
    if (abs(velocity.y) > SpeedLimit.y && velocity.y != 0)
    {
        velocity.y = SpeedLimit.y * (abs(velocity.y) / velocity.y);
    }
    
    if (abs(velocity.z) > SpeedLimit.z && velocity.z != 0)
    {
        velocity.z = SpeedLimit.z * (abs(velocity.z) / velocity.z);
    }
}