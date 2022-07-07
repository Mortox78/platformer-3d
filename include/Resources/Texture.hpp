#ifndef _Texture_
#define _Texture_

#include <string>

#include "ResourcesManager.hpp"

namespace Resources
{
    class Texture
    {
    public:
        unsigned int nbTexture;
        std::string name = "";
        bool loaded = false;
    
        Texture(){};
        Texture(const char *filename);
        ~Texture();
    
        static unsigned int LoadTexture(const char *filename);
        static void freeTexture(unsigned int &texture);

        friend std::ostream& operator<<(std::ostream& os, const Texture& texture)
        {
            os << texture.name << std::endl;

            return os;
        }

        friend std::istream& operator>>(std::istream& is, Texture& texture)
        {
            std::string textureName;
            is >> textureName;
            Resources::Texture textureLoaded = Resources::ResourcesManager::LoadTex(textureName.c_str());
            texture.nbTexture = textureLoaded.nbTexture;
            texture.name = textureLoaded.name;
            texture.loaded = textureLoaded.loaded;

            return is;
        }
    };
}

#endif