#pragma once

#include "System/keyboard_keys.hpp"

#include <unordered_map>
#include <functional>
#include <vector>
#include <bitset>

struct GLFWwindow;

class KeyboardInput{
public:
    KeyboardInput(GLFWwindow* window);

    void EndFrame();
    //All the below rely on polling, callbacks are not implemented
    bool IsKeyPressed(Key key);
    bool IsKeyHeld(Key key);
    bool IsKeyReleased(Key key);

    //using EventCallback = std::function<void()>;
    //void Subscribe(Key key, EventCallback callback);

private:

    std::bitset<512> m_CurrentKeys;
    std::bitset<512> m_PreviousKeys;
    
    // The GLFW callback still needs to be static to be passed as a C-pointer
    static void GLFW_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

};