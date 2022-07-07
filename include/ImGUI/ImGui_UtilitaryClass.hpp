#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <string>



struct InputManager;

struct ImGui_StorageClass
{
    ImGui_StorageClass(ImGuiStyle& _style, ImGuiIO& _IO)
        : style(_style), IO(_IO)
    {}
    
    ImGuiStyle& style;
    ImGuiIO&    IO;

    ImVec2      widowDimensions;
};


class ImGui_ToolClass
{
private:
    bool openOptions = false;
    bool loadingPanel = false;
    

    ImGuiContext*       context;

    GLFWwindow*         window;
    
    ImGui_StorageClass* components;


    InputManager&       inputs;


public:
    bool show = true;

    ImGui_ToolClass(GLFWwindow* _window, InputManager& _inputs);
    void Terminate();

    void BeginFrame();
    void EndFrame();

    void mainMenuInterface();
    void optionPannel(ImVec2 win);
};