#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <GLFW/glfw3.h>
#include <iostream>

#include <memory>

enum Key
{
    alpha_A, alpha_B, alpha_C, alpha_D, alpha_E, alpha_F, alpha_G, alpha_H, alpha_I, alpha_J, alpha_K, alpha_L, alpha_M, alpha_N, alpha_O, alpha_P, alpha_Q, alpha_R, alpha_S, alpha_T, alpha_U, alpha_V, alpha_W, alpha_X, alpha_Y, alpha_Z,    
    numeral_0, numeral_1, numeral_2, numeral_3, numeral_4, numeral_5, numeral_6, numeral_7, numeral_8, numeral_9,
    function_1, function_2, function_3, function_4, function_5, function_6, function_7, function_8, function_9, function_10, function_11, function_12, function_13, function_14, function_15, function_16, function_17, function_18, function_19, function_20, function_21, function_22, function_23, function_24, function_25,
    other_ESC, other_SPACE,

    NUM_OF_KEYS
};

enum Actions
{
    Pause,
    Left, Right, Forward, Backwards,
    Up, Down,
    Jump,
    Save,

    NUM_OF_ACTS
};

struct InputManager
{
    InputManager(GLFWwindow* _window);
    
    bool IsKeyPressed       (Key key);
    bool IsActionTriggered  (Actions act);

    void Remap(Actions act, Key key);

    void UpdateKeyboard();

    static const char* KeyName(Key keyNum);

    Key keyToAct_Map[Actions::NUM_OF_ACTS];
    
    Actions actionToRemap = Actions::NUM_OF_ACTS;
    bool    catchingInput = false;

private:
    GLFWwindow* window;
    bool inputs[Key::NUM_OF_KEYS] = {false};
    
    void CatchInput();
};


// Inlined functions

inline InputManager::InputManager(GLFWwindow* _window)
             : window(_window)
{
    keyToAct_Map[Actions::Pause]        = Key::other_ESC;
    
    keyToAct_Map[Actions::Left]         = Key::alpha_A;
    keyToAct_Map[Actions::Right]        = Key::alpha_D;
    keyToAct_Map[Actions::Forward]      = Key::alpha_W;
    keyToAct_Map[Actions::Backwards]    = Key::alpha_S;

    keyToAct_Map[Actions::Up]           = Key::alpha_E;
    keyToAct_Map[Actions::Down]         = Key::alpha_F;

    keyToAct_Map[Actions::Jump]         = Key::other_SPACE;

    keyToAct_Map[Actions::Save]         = Key::function_5;
}


inline bool InputManager::IsKeyPressed(Key key)
{
    return inputs[key];
}

inline bool InputManager::IsActionTriggered(Actions act)
{
    return IsKeyPressed( keyToAct_Map[act] );
}

inline void InputManager::Remap(Actions act, Key key)
{ keyToAct_Map[act] = key; }

inline void InputManager::UpdateKeyboard()
{
    glfwPollEvents();
    
    for ( short a = 0 ; a < 26 ; a++ )
    {
        inputs[a] = glfwGetKey(window, a + 65);
    }

    for ( short n = 0 ; n < 10 ; n++ )
    {
        inputs[25 + n] = glfwGetKey(window, n + 48);
    }

    for ( short f = 0 ; f < 25 ; f++ )
    {
        inputs[35 + f] = glfwGetKey(window, f + 290);
    }

    inputs[61] = glfwGetKey(window, GLFW_KEY_ESCAPE);
    inputs[62] = glfwGetKey(window, GLFW_KEY_SPACE);


    if (catchingInput) CatchInput();
}

inline void InputManager::CatchInput()
{
    for (short inputNum = 0 ; inputNum < Key::NUM_OF_KEYS ; inputNum++)
    {
        if (inputs[inputNum])
        {
            Remap(actionToRemap, static_cast<Key>(inputNum));

            actionToRemap = Actions::NUM_OF_ACTS;
            catchingInput = false;
            
            return;
        }
    }
}

// Tools

inline const char* InputManager::KeyName(Key keyNum)
{
    static char keyChar[1];
    
    if (keyNum <= Key::alpha_Z)
    {
        keyChar[0] = keyNum + 'a';
        
        return &keyChar[0];
    }

    if (keyNum > Key::alpha_Z && keyNum <= Key::numeral_9)
    {
        keyChar[0] = (keyNum - Key::alpha_Z) + '0';

        return &keyChar[0];
    }

    if (keyNum > Key::numeral_9 && keyNum <= Key::function_25)
    {
        keyChar[0] = (keyNum - Key::numeral_9) + 17;
    
        return &keyChar[0];
    }

    if (keyNum == Key::other_ESC)   return "ESC";
    if (keyNum == Key::other_SPACE) return "SPACE";

    return "?";
}

#endif