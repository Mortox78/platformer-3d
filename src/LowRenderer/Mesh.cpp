#include "Mesh.hpp"
#include "Shader.hpp"
#include "Transform.hpp"

using namespace LowRenderer;

Mesh::Mesh()
{}

Mesh::~Mesh()
{}

void Mesh::display(const Maths::Mat4 &projectionMat,  const Maths::Mat4 &viewMat, 
                 const std::vector<LowRenderer::Light> &lights, Maths::Mat4 TRS)
{

    // Use the shader
    shader->use();
    
    // Set the lights in the shader
    shader->SetAllLights(lights);

    // Set the matrices in the shader
    shader->SetMatrix(TRS * transform->getMatrix(), "Transform");
    shader->SetMatrix(viewMat               , "CameraTransform");
    shader->SetMatrix(projectionMat         , "CameraPerspective");
    shader->SetMatrix(complementaryMatrix   , "Complementary");
    
    for (unsigned int i = 0; i < models.size(); i++)// Set the texture to the corresponding model in the Mesh
    {
        if (i < textures.size())
        {
            glBindTexture(GL_TEXTURE_2D, textures[i].nbTexture); 
        }
        models[i].Draw();
    }
}