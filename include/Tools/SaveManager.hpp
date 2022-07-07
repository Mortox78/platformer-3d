#pragma once

#include "Scene.hpp"

struct SaveManager
{
    static void SaveGame(const Core::DataStructure::GameObject& player);
    static void LoadGame(Core::DataStructure::GameObject& player);
};