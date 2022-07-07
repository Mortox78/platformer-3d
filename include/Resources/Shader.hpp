#ifndef _SHADER_
#define _SHADER_

#include "matrix.hpp"

#include "ResourcesManager.hpp"

#include <iostream>

#include <ctime>
#include <cstdio>
#include <fstream>
#include <sstream>

using namespace Core;

namespace Resources
{
    class Shader
    {
    public:
        GLuint ID;

        Shader(){};
        Shader(const char *vertex_file_path, const char *fragment_file_path);
        ~Shader(){};

        static GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path);

        void use();
        void SetMatrix(const Maths::Mat4& matrix, const std::string &name); // set a matrix in the shader
        void SetAllLights(const std::vector<LowRenderer::Light> &lights); // set a list of light in the shader max 16
        void SetLight(const LowRenderer::Light& light, unsigned int number); // set a light in the shader

        void SetColor(Core::Maths::Vec4 color);

        friend std::ostream& operator<<(std::ostream& os, const Shader& shader)
        {
            os << shader.ID << std::endl;
            return os;
        }

        friend std::istream& operator>>(std::istream& is, Shader& shader)
        {
            is >> shader.ID;
            return is;
        }
    };
}

#endif