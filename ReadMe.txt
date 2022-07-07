Build : You can build this project by typing "make" in the console inside the folder that contains the project.
Run   : You can type "./bin/gl"  in the console or "make run" once the project is build

Information:

    You can move the camera with w, s, a, d, - and +
    You can stop the program by pressing the ESCAPE key
    
    The controls above are all re-mappable inside the "option" sub-menu of the main menu : click a button then press a key to remap it. Supported keys are aphabetic, numbers and function keys (F1 F2..).
    
    To start the game press "New game" from the main menu.

    The file use for shader are placed in "include/Resources/"

--- Developed features ---

- Core
    - vec2, vec3, vec4 and mat4
    - segment, oriented box, sphere, quad, plane and AABB
    - Graph
    - Assertion (incomplete)

- Resources
    - Model
    - Texture
    - Shader
    - Scene

- LowRenderer
    - Mesh
    - Model
    - Camera

- Physics
    - Transform
    - Collision sphere & oriented box, oriented box & oriented box, sphere & sphere, AABB & AABB, segment & sphere, segment & oriented box, segment & plane, cylinder infinte & segment, cylinder finish & segment, segment & quad and segment & AABB.

- Resources : 
    - ResourcesManager

- Tools (managers) :
    - TimeManager
    - InputManager
    - TimeManager
    
- ImGUI :
    - Main menu and options    

- Engine: 
    - the class gameobject is used to contain a mesh, a transform and a list of the class AddtitionalBehavior
    - the class AddtitionalBehavior allow to have several function link a game a object that are called each time the scene is read

 --- Undeveloped features ---

- Core 
    - Log



 --- Problem and Bug ---
 
    - parcer OBJ incomplete (can't read material file and can't separate element in a file (s,o,...))


Readme

Physics : 
    -Features:
        - We have geometrical form in directory Core/Maths (sphere, orientedBox, plane, cylinder ..).
        - We have collider for the geometrical form we made in the directory Physics.
        - There are the collision between a moving sphere and static cube the call is in C

    TO DO:
        - we don't have the glide.
        - we don't have the camera.

A beginning of save system is implemented in the project, it cans save only one gameobject.
The "SaveManager" is present in the files : 
"include/Tools/SaveManager.hpp"
"src/Tools/SaveManager.cpp"

The save system uses those surcharged operators in a lot of classes : "operator<<" and "operator>>"
We use both in order to make classes saveable in a ".txt"


- we don't have enemy.
- we don't have the level editor.