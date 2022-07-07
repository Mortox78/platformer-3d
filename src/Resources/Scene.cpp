#include "Scene.hpp"

void Resources::Scene::Display(const Core::Maths::Mat4 &projection, Core::Maths::Mat4 view,
    const std::vector<LowRenderer::Light> &lights, Core::Maths::Mat4 TRS)
{
    if (object)
    {
        object->Mesh().display(projection, view, lights, TRS);
        TRS = TRS * object->Mesh().transform->getMatrix();
    }
    
    for (unsigned int i = 0 ; i < list.size() ; i++)
    {
        list[i].Display(projection, view, lights, TRS);
    }
}

void Resources::Scene::Read(const Core::Maths::Mat4 &projection, Core::Maths::Mat4 view,
    const std::vector<LowRenderer::Light> &lights, Core::Maths::Mat4 TRS)
{
    if (object)
    {
        object->Update();
        object->Mesh().display(projection, view, lights, TRS);
        TRS = TRS * object->Mesh().transform->getMatrix();
    }
    
    for (unsigned int i = 0 ; i < list.size() ; i++)
    {
        list[i].Read(projection, view, lights, TRS);
    }
}
