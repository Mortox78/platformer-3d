#ifndef _RESOURCESMANAGER_
#define _RESOURCESMANAGER_

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>

#include <vector>

#include "Light.hpp"

namespace LowRenderer
{
    class Mesh;
}

namespace Resources
{
    class Texture;
    class Model;
    class ResourcesManager
    {
        public:
            ResourcesManager();
            ~ResourcesManager();

            static std::vector<Model>      models;
            static std::vector<Texture>    textures;

            // This function return a mesh with only one OBJ and one texture
            static LowRenderer::Mesh  LoadSingleMesh(const char* objFileName, const char* texFileName);
            static Resources::Model   LoadOBJ(const char* objFileName);
            static Resources::Texture LoadTex(const char* texFileName);
    };
}

#endif
