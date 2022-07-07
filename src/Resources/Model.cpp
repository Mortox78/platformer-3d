#include "Model.hpp"

using namespace Resources;
Model::Model(const std::vector<Vertex> &list, const Core::Maths::Vec4 &color)
{
    unsigned int count = 0;


    GLfloat Point[list.size() * MODEL_READ_SIZE];

    for (unsigned int i = 0; i < list.size(); i++)
    {
        Point[count + 0] = list[i].position.x;
        Point[count + 1] = list[i].position.y;
        Point[count + 2] = list[i].position.z;

        Point[count + 3] = list[i].normal.x;
        Point[count + 4] = list[i].normal.y;
        Point[count + 5] = list[i].normal.z;

        Point[count + 6] = list[i].texture.x;
        Point[count + 7] = list[i].texture.y;

        Point[count + 8 ] = list[i].color.x * color.x;
        Point[count + 9 ] = list[i].color.y * color.y;
        Point[count + 10] = list[i].color.z * color.z;
        Point[count + 11] = list[i].color.w * color.w;

        count += MODEL_READ_SIZE;
    }


    data.size = list.size();

    glGenBuffers(1, &data.buffer); // Generate 1 buffer, put the resulting identifier in buffer
    glBindBuffer(GL_ARRAY_BUFFER, data.buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Point), Point, GL_STATIC_DRAW);// Give our vertices to OpenGL.
}

Model::Model(const char *path)
{
    std::vector<Vertex> listVertex = LoadOBJ(path);
    Model instance = Model(listVertex);
    this->data = instance.data;

    data.loaded = true;
    data.name = path;
}


void Model::Draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, data.buffer);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, MODEL_READ_SIZE * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, MODEL_READ_SIZE * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, MODEL_READ_SIZE * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    // Color attribute
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, MODEL_READ_SIZE * sizeof(float), (void *)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);


    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, data.size);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
}


/// --- Create basic shapes --- ///

void Model::createQuad(std::vector<Vertex> &list, const Maths::Vec3 bottomLeft, const Maths::Vec3 bottomRight, const Maths::Vec3 topLeft,
                       const Maths::Vec3 topRight, const Maths::Vec3 normal)
{
    list.push_back({bottomLeft,  normal, {0, 1}});
    list.push_back({bottomRight, normal, {1, 1}});
    list.push_back({topLeft,     normal, {0, 0}});
    list.push_back({topLeft,     normal, {0, 0}});
    list.push_back({topRight,    normal, {1, 0}});
    list.push_back({bottomRight, normal, {1, 1}});
}

Model Model::CreateCube()
{
    std::vector<Vertex> list;

    // front //
    createQuad(list, {-0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, 0.5f},
               {-0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f}, {0,0,1});

    // back //
    createQuad(list, {0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f},
               {0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f}, {0,0,-1});
    // right //
    createQuad(list, {0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, -0.5f},
               {0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, -0.5f}, {1,0,0});

    // left //
    createQuad(list, {-0.5f, -0.5f, 0.5f}, {-0.5f, -0.5f, -0.5f},
               {-0.5f, 0.5f, 0.5f}, {-0.5f, 0.5f, -0.5f}, {-1,0,0});

    // bottom //
    createQuad(list, {-0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, 0.5f},
               {-0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f}, {0,-1,0});

    // top //
    createQuad(list, {-0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f},
               {-0.5f, 0.5f, -0.5f}, {0.5f, 0.5f, -0.5f}, {0,1,0});

    return Model(list);
}

Maths::Vec3 Model::get_sphere_point(int i, int j, int longitudeCount, int latitudeCount)
{
    float r = sin(i * (PI / longitudeCount));
    float x = cos(j * (2 * PI / latitudeCount)) * r;
    float y = cos(i * (PI / longitudeCount));
    float z = sin(j * (2 * PI / latitudeCount)) * r;
    return {x, y, z};
}

Model Model::CreateSphere(int latitudeCount, int longitudeCount)
{
    std::vector<Vertex> sphere;

    for (int i = 0; i < longitudeCount; ++i)
        for (int j = 0; j < latitudeCount; ++j)
            createQuad(sphere, get_sphere_point(i, j, longitudeCount, latitudeCount),
                       get_sphere_point(i + 1, j, longitudeCount, latitudeCount),
                       get_sphere_point(i, j + 1, longitudeCount, latitudeCount),
                       get_sphere_point(i + 1, j + 1, longitudeCount, latitudeCount),
                       {0,1,0});

    return Model(sphere);
}

/// --- Read .obj files --- ///

unsigned int Model::NbSlash(const std::string &line)
{
    unsigned int count = 0;
    for (unsigned int i = 0; i < line.size() - 1; i++)
    {
        if (line[i] == '/')
            count++;
    }
    return count;
}

void Model::AddVertex(std::vector<Vertex>     &out_vertices,
                const std::vector<int>  &vertexIndices,
                const std::vector<int>  &uvIndices,
                const std::vector<int>  &normalIndices,
                const std::vector<Maths::Vec3> &temp_vertices,
                const std::vector<Maths::Vec2> &temp_uvs,
                const std::vector<Maths::Vec3> &temp_normals)
{
    // For each vertex of each triangle
    for (unsigned int i = 0; i < vertexIndices.size(); i++)
    {
        Vertex vertexTemp;

        if (vertexIndices[i] > 0)
            vertexTemp.position = temp_vertices[vertexIndices[i] - 1];
        else if (vertexIndices[i] < 0)
            vertexTemp.position = temp_vertices[temp_vertices.size() + vertexIndices[i]];

        if (uvIndices[i] > 0)
            vertexTemp.texture = temp_uvs[uvIndices[i] - 1];
        else if (uvIndices[i] < 0)
            vertexTemp.texture = temp_uvs[temp_uvs.size() + uvIndices[i]];

        if (normalIndices[i] > 0)
            vertexTemp.normal = temp_normals[normalIndices[i] - 1];
        else if (normalIndices[i] < 0)
            vertexTemp.normal = temp_normals[temp_normals.size() + normalIndices[i]];

        out_vertices.push_back(vertexTemp);
    }
}

std::vector<Vertex> Model::LoadOBJ(const std::string &path)
{
    using namespace Core::Maths;
    
    std::vector<Vertex> out_vertices;

    std::ifstream in(path, std::ios::in);
    if (!in) {std::cerr << "Impossible to open " << path << std::endl; exit(EXIT_FAILURE);}
    
    bool isTextured = false,
         hasNormals = false;

    std::string line;

    std::vector<Vec3        > vertexPos;
    std::vector<unsigned int> vertexHint;

    std::vector<Vec2        > texturePos;
    std::vector<unsigned int> textureHints;

    std::vector<Vec3        > normalPos;
    std::vector<unsigned int> normalHints;

    while(getline(in, line))
    {
        if      (line.substr(0, 2) == "v ")
        {
            std::istringstream s(line.substr(2));
            Vec3 vP; s >> vP.x; s >> vP.y; s >> vP.z;

            vertexPos.push_back(vP);
        }
        else if (line.substr(0, 3) == "vt ")
        {
            std::istringstream s(line.substr(3));
            Vec2 vTp; s >> vTp.x; s >> vTp.y;

            texturePos.push_back(vTp);

            isTextured = true;
        }
        else if (line.substr(0, 3) == "vn ")
        {
            std::istringstream s(line.substr(3));
            Vec3 nP; s >> nP.x; s >> nP.y; s >> nP.z;

            normalPos.push_back(nP);
            
            hasNormals = true;
        }
        else if (line.substr(0, 2) == "f ")
        {
            std::istringstream s(line.substr(2));
            unsigned int vI  [12];
            char         dump;

            s >> vI[0];

            if (s.peek() == '/')
            {
                if (!hasNormals) // partial go
                {
                                s >> dump; s >> vI[1];
                    s >> vI[2]; s >> dump; s >> vI[3];
                    s >> vI[4]; s >> dump; s >> vI[5];

                    vertexHint.push_back(vI[0]); textureHints.push_back(vI[1]);
                    vertexHint.push_back(vI[4]); textureHints.push_back(vI[5]);
                    vertexHint.push_back(vI[2]); textureHints.push_back(vI[3]);

                    s >> vI[6];

                    if (s.peek() == '/')
                    {
                        s >> dump; s >> vI[7];

                        vertexHint.push_back(vI[0]); textureHints.push_back(vI[1]);
                        vertexHint.push_back(vI[4]); textureHints.push_back(vI[5]);
                        vertexHint.push_back(vI[6]); textureHints.push_back(vI[7]);
                    }
                }
                else // Full go
                {
                                s >> dump; s >> vI[1]; s >> dump; s >> vI[2];
                    s >> vI[3]; s >> dump; s >> vI[4]; s >> dump; s >> vI[5];
                    s >> vI[6]; s >> dump; s >> vI[7]; s >> dump; s >> vI[8];

                    vertexHint.push_back(vI[0]); textureHints.push_back(vI[ 1]); normalHints.push_back(vI[ 2]);
                    vertexHint.push_back(vI[6]); textureHints.push_back(vI[ 7]); normalHints.push_back(vI[ 8]);
                    vertexHint.push_back(vI[3]); textureHints.push_back(vI[ 4]); normalHints.push_back(vI[ 5]);

                    s >> vI[9];

                    if (s.peek() == '/')
                    {
                        s >> dump; s >> vI[10]; s >> dump; s >> vI[11];
                        
                        vertexHint.push_back(vI[0]); textureHints.push_back(vI[ 1]); normalHints.push_back(vI[ 2]);
                        vertexHint.push_back(vI[6]); textureHints.push_back(vI[ 7]); normalHints.push_back(vI[ 8]);
                        vertexHint.push_back(vI[9]); textureHints.push_back(vI[10]); normalHints.push_back(vI[11]);
                    }
                }
                
            }
            else                    // Simplified analisis with vertexH only x3 or x4.
            {
                s >> vI[ 1]; s >> vI[ 2];

                vertexHint.push_back(vI[0]);
                vertexHint.push_back(vI[2]);
                vertexHint.push_back(vI[1]);

                if (!s.eof())
                {
                    s >> vI[3];

                    vertexHint.push_back(vI[0]);
                    vertexHint.push_back(vI[2]);
                    vertexHint.push_back(vI[3]);
                }     
            }
            
            
        }
        else
        {/* Ignored ! */}    
    }
    
    for (size_t i = 0 ; i < vertexHint.size() || i < textureHints.size() ; i++)
    {
        out_vertices.push_back
        ({              vertexPos [vertexHint  [i] -1], 
           hasNormals ? normalPos [normalHints [i] -1] : vertexPos[vertexHint[i] -1].Normalize(),
           isTextured ? texturePos[textureHints[i] -1] : Vec2{0, 0} });
    }
    
    static short modelNumber = 0;
    modelNumber++;

    std::cout << "-- Model [" << modelNumber << "] loaded --" << std::endl;
    std::cout << "Length   : " << out_vertices.size()         << std::endl;
    std::cout << "Capacity : " << out_vertices.capacity()     << std::endl << std::endl;

    return out_vertices;
}
