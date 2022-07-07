#include "Shader.hpp"

#include "Light.hpp"

using namespace Resources;

Shader::Shader(const char *vertex_file_path, const char *fragment_file_path)
{
    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if (VertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }
    else
    {
        printf("Impossible to open %s.\n", vertex_file_path);
        getchar();
        return;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if (FragmentShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    char const *VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    // Compile Fragment Shader
    char const *FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    // Link the program
    ID = glCreateProgram();
    glAttachShader(ID, VertexShaderID);
    glAttachShader(ID, FragmentShaderID);
    glLinkProgram(ID);

    // Check the program
    glGetProgramiv(ID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(ID, VertexShaderID);
    glDetachShader(ID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return;
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::SetMatrix(const Maths::Mat4 &matrix, const std::string &name)
{
    // Get the matrix for the Shader
    GLuint MatrixID = glGetUniformLocation(ID, name.c_str());

    // Send our transformation to the currently bound shader, in the coresponding uniform matrix
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, matrix.array);
}

GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path)
{

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if (VertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }
    else
    {
        printf("Impossible to open %s.\n", vertex_file_path);
        getchar();
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if (FragmentShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    char const *VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    // Compile Fragment Shader
    char const *FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    // Link the program
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

void Shader::SetAllLights(const std::vector<LowRenderer::Light> &lights)
{
    int location = glGetUniformLocation(ID, "nbLights");
    glUniform1f(location, lights.size());
    for (size_t i = 0 ; i < lights.size() ; i++)
    {
        SetLight(lights[i], i);
    }
}

void Shader::SetLight(const LowRenderer::Light& light, unsigned int number) // Set the info 
{
    std::string set         = "lights[" + std::to_string(number);
    std::string position    = "].position";
    std::string direction   = "].direction";
    std::string ambient     = "].ambient";
    std::string diffuse     = "].diffuse";
    std::string specular    = "].specular";
    std::string spotAngle   = "].spotAngle";
    std::string constant    = "].constant";
    std::string linear      = "].linear";
    std::string quadratic    = "].quadratic";

    int location = glGetUniformLocation(ID, (set + position).c_str());
    glUniform3f(location, light.position.x, light.position.y, light.position.z);

    location = glGetUniformLocation(ID, (set + direction).c_str());
    glUniform3f(location, light.direction.x, light.direction.y, light.direction.z);

    location = glGetUniformLocation(ID, (set + ambient).c_str());
    glUniform3f(location, light.ambient.x, light.ambient.y, light.ambient.z);

    location = glGetUniformLocation(ID, (set + diffuse).c_str());
    glUniform3f(location, light.diffuse.x, light.diffuse.y, light.diffuse.z);

    location = glGetUniformLocation(ID, (set + specular).c_str());
    glUniform3f(location, light.specular.x, light.specular.y, light.specular.z);

    location = glGetUniformLocation(ID, (set + spotAngle).c_str());
    glUniform1f(location, light.spotAngle);

    location = glGetUniformLocation(ID, (set + constant).c_str());
    glUniform1f(location, light.constant);
    
    location = glGetUniformLocation(ID, (set + linear).c_str());
    glUniform1f(location, light.linear);
    
    location = glGetUniformLocation(ID, (set + quadratic).c_str());
    glUniform1f(location, light.quadratic);
}

void Shader::SetColor(Core::Maths::Vec4 color)
{
    int location = glGetUniformLocation(ID, "Color");
    glUniform4f(location, color.x, color.y, color.z, color.w);
}
