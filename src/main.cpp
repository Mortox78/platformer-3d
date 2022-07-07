#include "Mesh.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "Assertion.hpp"
#include "ResourcesManager.hpp"

#include "TimeManager.hpp"

#include "AdditionalBehavior.hpp"

#include "GameObject.hpp"

#include "SaveManager.hpp"
#include "InputManager.hpp"

#include <iostream>

#include "Collider.hpp"
#include "OrientedBoxCollider.hpp"

#include "CharacterPhysicBody.hpp"

#include "ImGui_UtilitaryClass.hpp"


int main(int argc, char *argv[])
{
    Resources::ResourcesManager resourcesManager;
    int screenWidth = 800;
    int screenHeight = 600;

    // Init GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "glfwInit failed.\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    // Create window
    GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "Fenaitre", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "glfwCreateWindow failed.\n");
        glfwTerminate();
        return -1;
    }

    glfwSwapInterval(1); // Enable v-sync

    glfwMakeContextCurrent(window);

    // Load OpenGL functions
    if (!gladLoadGL())
    {
        fprintf(stderr, "gladLoadGL failed.\n");
        glfwTerminate();
        return -1;
    }

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create and compile our GLSL program from the shaders
    Resources::Shader textureID("include/Resources/Shader/BasicVertexShader.vs", "include/Resources/Shader/TextureFragmentShader.fs");
    Resources::Shader simpleID ("include/Resources/Shader/BasicVertexShader.vs", "include/Resources/Shader/ColorFragmentShader.fs");


    float rot = 0;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    Tools::Time timeManager;
    timeManager.Update();

    Physics::Transform trsPlayer({0,0,0}, {0.1, 0.1, 0.1}, {0, 0, 0});

    Physics::Transform trsGround({0,0,0}, {10, 10, 10}, {0, 0, 0});

   
    Core::DataStructure::GameObject player;

    #if 1

    player.transform = Physics::Transform({0,50,0}, {1, 1, 1}, {-PI / 2, 0, 0});

    player.Mesh().models.push_back(Resources::Model::CreateSphere(100,100));
    //player.Mesh().models.push_back(resourcesManager.LoadOBJ("./resources/Dog.obj"));
    player.Mesh().shader = &simpleID;
    #else
    SaveManager::LoadGame(player);
    #endif

    player.AddBehavior(new Physics::CharacterPhysicBody());

    Core::DataStructure::GameObject ground;
    Core::DataStructure::GameObject ground2;
    Core::DataStructure::GameObject ground3;
    Core::DataStructure::GameObject ground4;
    Core::DataStructure::GameObject ground5;
    Core::DataStructure::GameObject ground6;

    ground.transform = trsGround;

    ground.AddBehavior(new Physics::OrientedBoxCollider());

    ground.Mesh().models.push_back(Resources::Model::CreateCube());
    ground.Mesh().textures.push_back(resourcesManager.LoadTex("./resources/DirtCube.jpg"));
    ground.Mesh().shader = &textureID;

    
    ground2.transform =  Physics::Transform({10,10,0}, {10, 10, 10}, {0, 0, 0});
    ground2.AddBehavior(new Physics::OrientedBoxCollider());
    ground2.Mesh().models.push_back(Resources::Model::CreateCube());
    ground2.Mesh().textures.push_back(resourcesManager.LoadTex("./resources/DirtCube.jpg"));
    ground2.Mesh().shader = &textureID;

    ground3.transform =  Physics::Transform({-10,10,0}, {10, 10, 10}, {0, 0, 0});
    ground3.AddBehavior(new Physics::OrientedBoxCollider());
    ground3.Mesh().models.push_back(Resources::Model::CreateCube());
    ground3.Mesh().textures.push_back(resourcesManager.LoadTex("./resources/DirtCube.jpg"));
    ground3.Mesh().shader = &textureID;

    ground4.transform =  Physics::Transform({0,10,10}, {10, 10, 10}, {0, 0, 0});
    ground4.AddBehavior(new Physics::OrientedBoxCollider());
    ground4.Mesh().models.push_back(Resources::Model::CreateCube());
    ground4.Mesh().textures.push_back(resourcesManager.LoadTex("./resources/DirtCube.jpg"));
    ground4.Mesh().shader = &textureID;

    ground5.transform =  Physics::Transform({0,10,-10}, {10, 10, 10}, {0, 0, 0});
    ground5.AddBehavior(new Physics::OrientedBoxCollider());
    ground5.Mesh().models.push_back(Resources::Model::CreateCube());
    ground5.Mesh().textures.push_back(resourcesManager.LoadTex("./resources/DirtCube.jpg"));
    ground5.Mesh().shader = &textureID;

    ground6.transform =  Physics::Transform({0,30,0}, {10, 10, 10}, {0, 0, 0});
    ground6.AddBehavior(new Physics::OrientedBoxCollider());
    ground6.Mesh().models.push_back(Resources::Model::CreateCube());
    ground6.Mesh().textures.push_back(resourcesManager.LoadTex("./resources/wall.jpg"));
    ground6.Mesh().shader = &textureID;


    LowRenderer::Light light;

    light.position  = {0, 0, 0};
    light.ambient   = {0.1f , 0.1f, 0.1f};
    light.direction = {0.0f , -1.0f, 0.0f};
    light.diffuse   = {0.8f , 0.8f, 0.8f};
    light.specular  = {0.0f , 0.0f, 0.0f};
    light.spotAngle = 0;
    light.constant  = 1.0f;
    light.linear    = 0.00;
    light.quadratic = 0.00;

    std::vector<LowRenderer::Light> lights;
    lights.push_back(light);
    
    Resources::Scene world;

    world.Add(&player);
    world.Add(&ground);
    world.Add(&ground2);
    world.Add(&ground3);
    world.Add(&ground4);
    world.Add(&ground5);
    world.Add(&ground6);

    // Main loop

    Maths::Vec3 position = {0, 10, 50};

    LowRenderer::Camera camera(25, screenWidth, screenHeight, 0.01, 500);
    camera.position = position;

    timeManager.Update();
    
    Core::DataStructure::AdditionalBehavior* chara = player.GetBehavior(CHARACTER_PHYSIC_BODY);
    Physics::CharacterPhysicBody* phB = (Physics::CharacterPhysicBody*)chara;

    phB->SpeedLimit.y = 10;

    InputManager    inputs(window);
    ImGui_ToolClass imGui(window, inputs);

    while (!glfwWindowShouldClose(window))
    {
        timeManager.Update();
        inputs.UpdateKeyboard();

        if (imGui.show)
        {
            imGui.BeginFrame();

            imGui.mainMenuInterface();

            imGui.EndFrame();
        }
        else
        {
            camera.SetLookAt(player.transform.position, player.transform.position + Core::Maths::Vec3{0,50,-20}, {0,1,0});

            if (glfwGetKey(window, GLFW_KEY_ESCAPE))
                glfwSetWindowShouldClose(window, 1);


            if (inputs.IsActionTriggered(Actions::Save))
                SaveManager::SaveGame(player);
            if (inputs.IsActionTriggered(Actions::Right))
                phB->AddForce(Vec3{-1,0,0} * timeManager.deltaTime);
            if (inputs.IsActionTriggered(Actions::Left))
                phB->AddForce(Vec3{1,0,0} * timeManager.deltaTime);
            if (inputs.IsActionTriggered(Actions::Forward))
                phB->AddForce(Vec3{0,0,1} * timeManager.deltaTime);
            if (inputs.IsActionTriggered(Actions::Backwards))
                phB->AddForce(Vec3{0,0,-1} * timeManager.deltaTime);
            if (inputs.IsActionTriggered(Actions::Up))
                player.transform.position.y += 1 * timeManager.deltaTime;
            if (inputs.IsActionTriggered(Actions::Down))
                player.transform.position.y -= 1 * timeManager.deltaTime;
            if (inputs.IsActionTriggered(Actions::Jump))
            {
                phB->AddForce({0,1,0});
            }


            // Set all the pixel of the screen to the same color (here black)
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            world.Read(camera.GetMatrixPerspective() , camera.GetMatrixTransformation(), lights);
        }

        // Present buffer
        glfwSwapBuffers(window);

        rot += 1 / (365.25 / 2 * PI );
    }

    imGui.Terminate();
    glfwTerminate();


    return 0;
}