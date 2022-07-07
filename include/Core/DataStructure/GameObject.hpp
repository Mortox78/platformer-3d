#ifndef _GAMEOBJECT_
#define _GAMEOBJECT_

#include "Mesh.hpp"
#include "Transform.hpp"

#include "AdditionalBehavior.hpp"

namespace Core
{
    namespace DataStructure
    {
        typedef class Mesh Mesh;

        class GameObject
        {
        private:
            LowRenderer::Mesh mesh;
            //std::vector<std::shared_ptr<AdditionalBehavior>> listBehavior;
            std::vector<AdditionalBehavior*> listBehavior;

        public:
            Physics::Transform transform;
            
            GameObject(){};
            ~GameObject(){};

            LowRenderer::Mesh& Mesh()
            {
                if (mesh.transform != &transform)
                    mesh.transform = &transform;
                return mesh; 
            };

            AdditionalBehavior *GetBehavior(std::string behavName)
            {
                for (unsigned i = 0; i < listBehavior.size(); i++)
                {
                    if (listBehavior[i]->name == behavName)
                    {
                        return listBehavior[i];
                    }
                }
                return nullptr;
            }

            void AddBehavior(AdditionalBehavior *newBehavior)
            {
                listBehavior.push_back(newBehavior);
                listBehavior[listBehavior.size() - 1]->Start(&transform);
            }

            void Update()
            {
                for (unsigned i = 0; i < listBehavior.size(); i++)
                {
                    listBehavior[i]->Update();
                }
            }
            
            friend std::ostream& operator<<(std::ostream& os, const GameObject& player)
            {
                os << player.mesh;
                os << player.transform;
                return os;
            }

            friend std::istream& operator>>(std::istream& is, GameObject& player)
            {
                is >> player.mesh >> player.transform;
                return is;
            }
        };
    }   
}

#endif