#ifndef _SCENE_
#define _SCENE_

#include "Graph.hpp"
#include "Light.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"

#include "GameObject.hpp"

namespace Resources
{

    class Scene : public Core::DataStructure::Graph<Core::DataStructure::GameObject, Scene>
    {
    public:
        Scene()  = default;
        ~Scene() = default;
    
        void Display(const Core::Maths::Mat4 &projection, Core::Maths::Mat4 view,
                     const std::vector<LowRenderer::Light> &lights, Core::Maths::Mat4 TRS = Maths::Mat4::GetIdentityMatrix());

        void Read(const Core::Maths::Mat4 &projection, Core::Maths::Mat4 view,
                     const std::vector<LowRenderer::Light> &lights, Core::Maths::Mat4 TRS = Maths::Mat4::GetIdentityMatrix());
    };

}


#endif