#include "ImGUI/ImGui_UtilitaryClass.hpp"
#include "Tools/InputManager.hpp"


ImGui_ToolClass::ImGui_ToolClass(GLFWwindow* _window, InputManager& _inputs)
               : window     (_window),
                 inputs     (_inputs),
                 context    (ImGui::CreateContext())
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();

    components = new ImGui_StorageClass(ImGui::GetStyle(), ImGui::GetIO());

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    ImGui::StyleColorsClassic();
}

void ImGui_ToolClass::BeginFrame()
{
    int x, y;
    glfwGetWindowSize(window, &x, &y);

    components->widowDimensions = {static_cast<float>(x), static_cast<float>(y)};
    

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGui_ToolClass::mainMenuInterface()
{
    components->style.WindowTitleAlign = {0.5f, 0.5f};
    components->style.FrameRounding = 20.f;

    ImVec2 win = components->widowDimensions;
    
    ImGui::Begin("< < M A I N  M E N U > >", nullptr, ImGuiWindowFlags_NoResize
                                                    | ImGuiWindowFlags_NoMove
                                                    | ImGuiWindowFlags_NoScrollWithMouse
                                                    | ImGuiWindowFlags_NoCollapse);

    ImGui::SetWindowPos({0, 0});
    ImGui::SetWindowSize({win.x, win.y});

    ImGui::SameLine(-1);
    if ( ImGui::Button("New game", {win.x /2 -5, win.y /3}) )
    { show = false; }

    ImGui::SameLine();
    if ( ImGui::Button("Load game", {win.x /2 -5, win.y /3}) )
    { loadingPanel = true; }

    ImGui::NewLine();
    ImGui::SameLine(win.x /4);
    if ( ImGui::Button("Options", {win.x /2, win.y /3}))
    { openOptions = true; }

    ImGui::NewLine(), ImGui::Spacing(), ImGui::NewLine(), ImGui::Spacing();
    ImGui::SameLine(win.x /2.f - win.x /8.f);
    if ( ImGui::Button("EXIT", {win.x /4, win.y /6}) )
    { glfwSetWindowShouldClose(window, 1); }

    ImGui::End();

    if ( openOptions )
    {
        optionPannel(win);
    }
}

void ImGui_ToolClass::optionPannel(ImVec2 win)
{
    using namespace ImGui;
    
    Begin("> >  O P T I O N  < <", (inputs.catchingInput ? nullptr : &openOptions), ImGuiWindowFlags_NoResize
                                                                                  | ImGuiWindowFlags_NoMove
                                                                                  | ImGuiWindowFlags_NoCollapse);

    SetWindowPos({0, 0});
    SetWindowSize({win.x, win.y});

    if (!inputs.catchingInput)
    {
        Text("Pause button");
        if ( Button(InputManager::KeyName(inputs.keyToAct_Map[Actions::Pause]), {300, 150}) )
        {
            inputs.actionToRemap = Actions::Pause; 
            inputs.catchingInput = true;
        }

        Text("Forward input");
        if ( Button(InputManager::KeyName(inputs.keyToAct_Map[Actions::Forward]), {300, 150}) )
        {
            inputs.actionToRemap = Actions::Forward;
            inputs.catchingInput = true;
        }

        Text("Backward input");
        if ( Button(InputManager::KeyName(inputs.keyToAct_Map[Actions::Backwards]), {300, 150}) )
        {
            inputs.actionToRemap = Actions::Backwards;
            inputs.catchingInput = true;
        }

        Text("Left input");
        if ( Button(InputManager::KeyName(inputs.keyToAct_Map[Actions::Left]), {300, 150}) )
        {
            inputs.actionToRemap = Actions::Left;
            inputs.catchingInput = true;
        }

        Text("Right input");
        if ( Button(InputManager::KeyName(inputs.keyToAct_Map[Actions::Right]), {300, 150}) )
        {
            inputs.actionToRemap = Actions::Right;
            inputs.catchingInput = true;
        }

        Text("Up input");
        if ( Button(InputManager::KeyName(inputs.keyToAct_Map[Actions::Up]), {300, 150}) )
        {
            inputs.actionToRemap = Actions::Up;
            inputs.catchingInput = true;
        }

        Text("Down input");
        if ( Button(InputManager::KeyName(inputs.keyToAct_Map[Actions::Down]), {300, 150}) )
        {
            inputs.actionToRemap = Actions::Down;
            inputs.catchingInput = true;
        }

        Text("Jump input");
        if ( Button(InputManager::KeyName(inputs.keyToAct_Map[Actions::Jump]), {300, 150}) )
        {
            inputs.actionToRemap = Actions::Jump;
            inputs.catchingInput = true;
        }

        Text("Save trigger");
        if ( Button(InputManager::KeyName(inputs.keyToAct_Map[Actions::Save]), {300, 150}) )
        {
            inputs.actionToRemap = Actions::Save;
            inputs.catchingInput = true;
        }
    }
    else // ============================================================================================
    {
        Text("Pause button");
        if ( Button(inputs.actionToRemap == Actions::Pause ?        "Press a key" : InputManager::KeyName(inputs.keyToAct_Map[Actions::Pause])      , {300, 150}) )
        {
            if (inputs.actionToRemap == Actions::Pause) inputs.catchingInput = false;
            inputs.actionToRemap = Actions::Pause; 
        }

        Text("Forward input");
        if ( Button(inputs.actionToRemap == Actions::Forward ?      "Press a key" : InputManager::KeyName(inputs.keyToAct_Map[Actions::Forward])    , {300, 150}) )
        {
            if (inputs.actionToRemap == Actions::Forward) inputs.catchingInput = false;
            inputs.actionToRemap = Actions::Forward;
        }

        Text("Backward input");
        if ( Button(inputs.actionToRemap == Actions::Backwards ?    "Press a key" : InputManager::KeyName(inputs.keyToAct_Map[Actions::Backwards])  , {300, 150}) )
        {
            if (inputs.actionToRemap == Actions::Backwards) inputs.catchingInput = false;
            inputs.actionToRemap = Actions::Backwards;
        }

        Text("Left input");
        if ( Button(inputs.actionToRemap == Actions::Left ?         "Press a key" : InputManager::KeyName(inputs.keyToAct_Map[Actions::Left])       , {300, 150}) )
        {
            if (inputs.actionToRemap == Actions::Left) inputs.catchingInput = false;
            inputs.actionToRemap = Actions::Left;
        }

        Text("Right input");
        if ( Button(inputs.actionToRemap == Actions::Right ?        "Press a key" : InputManager::KeyName(inputs.keyToAct_Map[Actions::Right])      , {300, 150}) )
        {
            if (inputs.actionToRemap == Actions::Right) inputs.catchingInput = false;
            inputs.actionToRemap = Actions::Right;
        }

        Text("Up input");
        if ( Button(inputs.actionToRemap == Actions::Up ?           "Press a key" : InputManager::KeyName(inputs.keyToAct_Map[Actions::Up])         , {300, 150}) )
        {
            if (inputs.actionToRemap == Actions::Up) inputs.catchingInput = false;
            inputs.actionToRemap = Actions::Up;
        }

        Text("Down input");
        if ( Button(inputs.actionToRemap == Actions::Down ?         "Press a key" : InputManager::KeyName(inputs.keyToAct_Map[Actions::Down])       , {300, 150}) )
        {
            if (inputs.actionToRemap == Actions::Down) inputs.catchingInput = false;
            inputs.actionToRemap = Actions::Down;
        }

        Text("Jump input");
        if ( Button(inputs.actionToRemap == Actions::Jump ?         "Press a key" : InputManager::KeyName(inputs.keyToAct_Map[Actions::Jump])       , {300, 150}) )
        {
            if (inputs.actionToRemap == Actions::Jump) inputs.catchingInput = false;
            inputs.actionToRemap = Actions::Jump;
        }

        Text("Save trigger");
        if ( Button(inputs.actionToRemap == Actions::Save ?         "Press a key" : InputManager::KeyName(inputs.keyToAct_Map[Actions::Save])       , {300, 150}) )
        {
            if (inputs.actionToRemap == Actions::Save) inputs.catchingInput = false;
            inputs.actionToRemap = Actions::Save;
        }
    }
    

    End();
}

void ImGui_ToolClass::EndFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void ImGui_ToolClass::Terminate()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(context);
}