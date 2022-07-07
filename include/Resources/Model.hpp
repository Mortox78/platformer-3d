#ifndef _MODEL_
#define _MODEL_

#include <limits.h>
#include <cstdlib>

#include "Shader.hpp"
#include "Vertex.hpp"

#define MODEL_READ_SIZE 12

struct modelBufferData
{
    GLuint buffer;
    size_t size;
    std::string name;
    bool loaded = false;
};

namespace Resources
{
    class Model
    {    
    public:
        modelBufferData data;
    
        Model(){};
        Model(const GLfloat *g_vertex_buffer_data, unsigned int sizeVertices, const GLfloat *g_color_buffer_data, unsigned int sizeColors, unsigned int Triangles = UINT_MAX);
        Model(const std::vector<Vertex> &list, const Core::Maths::Vec4 &color = {1,1,1,1});
        //Model(const std::vector<Vertex> &list, const std::vector<unsigned int> &indices);
        Model(const char *path);
        ~Model(){};
    
        void Draw();
    
        void SetModel();
    
        /*  Functions   */

        static unsigned int NbSlash(const std::string &line);

        static void AddVertex(std::vector<Vertex>    &out_vertices,
                        const std::vector<int>         &vertexIndices,
                        const std::vector<int>         &uvIndices,
                        const std::vector<int>         &normalIndices,
                        const std::vector<Maths::Vec3> &temp_vertices,
                        const std::vector<Maths::Vec2> &temp_uvs,
                        const std::vector<Maths::Vec3> &temp_normals);

        static std::vector<Vertex> LoadOBJ(const std::string &path); // create a list that can be used to set a model
    


        static void createQuad(std::vector<Vertex> &list, const Maths::Vec3 bottomLeft, const Maths::Vec3 bottomRight, const Maths::Vec3 topLeft,
                               const Maths::Vec3 topRight, const Maths::Vec3 normal);
    
        static Model CreateCube();
        static Maths::Vec3 get_sphere_point(int i, int j, int longitudeCount, int latitudeCount);
        static Model CreateSphere(int latitudeCount, int longitudeCount);

        friend std::ostream& operator<<(std::ostream& os, const Model& model)
        {
            os << model.data.name << std::endl;

            return os;
        }

        friend std::istream& operator>>(std::istream& is, Model& model)
        {
            std::string modelName;
            is >> modelName;
            
            Resources::Model loadedModel = Resources::ResourcesManager::LoadOBJ(modelName.c_str());

            model.data = loadedModel.data;

            return is;
        }
    };
}

#endif