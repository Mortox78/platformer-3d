#include <iostream>
#include <fstream>

#include "SaveManager.hpp"
#include "Scene.hpp"

void SaveManager::SaveGame(const Core::DataStructure::GameObject& player)
{
    std::ofstream file("save.txt");

    if (file.fail())
    {
        std::cout << "Error while opening \"save.txt\"" << std::endl;
    }
    else
    {
        std::cout << "\"save.txt\" opened" << std::endl;

        file << player;
    }

    file.close();
}

void SaveManager::LoadGame(Core::DataStructure::GameObject& player)
{
    std::ifstream file("save.txt");

    if (file.fail())
    {
        std::cout << "Error while opening \"save.txt\"" << std::endl;
    }
    else
    {
        std::cout << "\"save.txt\" opened" << std::endl;

        file >> player;
    }

    file.close();
}