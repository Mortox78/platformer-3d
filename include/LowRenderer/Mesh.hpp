#ifndef _MESH_
#define _MESH_

#include <memory>

#include "Shader.hpp"
#include "Transform.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

//#include "GameObject.hpp"

//#include "Collider.hpp"

namespace LowRenderer
{
    typedef class GameObject GameObject;
    class Mesh 
    {
    private:
        //Physics::Collider                *collider;
    
    public:
        std::vector<Resources::Model>    models; // I use a lists to change texture if their are several model
        std::vector<Resources::Texture>  textures;
        Resources::Shader                *shader;
        Physics::Transform               *transform;
        Maths::Mat4                      complementaryMatrix {Maths::Mat4::GetIdentityMatrix()}; // use to add effect to object (position)

        //GameObject                       *gameObject;


        Mesh();
        Mesh(std::string path);
        ~Mesh();

        void                display     (const Maths::Mat4 &projectionMat,  const Maths::Mat4 &viewMat, // matrices use for the camera
                                        const std::vector<LowRenderer::Light> &lights, 
                                        Maths::Mat4 TRS = Maths::Mat4::GetIdentityMatrix()); // matrix use to pass the transformation of the parent object

        //void                SetCollider (Physics::Collider* _collider);

        friend std::ostream& operator<<(std::ostream& os, const Mesh& mesh)
        {
                // save models
            for (unsigned int i = 0; i < mesh.models.size(); i++)
            {
                os << mesh.models[i];
            }
            // save textures
            for (unsigned int i = 0; i < mesh.textures.size(); i++)
            {
                os << mesh.textures[i];
            }

            os << *mesh.shader;
            os << *mesh.transform;
            os << mesh.complementaryMatrix;

            return os;
        }

        friend std::istream& operator>>(std::istream& is, Mesh& mesh)
        {
            // save models
            for (unsigned int i = 0; i < 1; i++)
            {
                Resources::Model modelLoaded;
                is >> modelLoaded;
                mesh.models.push_back(modelLoaded);
            }
            // save textures
            for (unsigned int i = 0; i < 1; i++)
            {
                Resources::Texture textureLoaded;
                is >> textureLoaded;
                mesh.textures.push_back(textureLoaded);
            }

            is >> *mesh.shader;
            is >> *mesh.transform;
            is >> mesh.complementaryMatrix;

            return is;
        }
    };
}


#endif