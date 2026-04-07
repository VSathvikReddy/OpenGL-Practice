#include "System/keyboard_input.hpp"
#include "System/engine_context.hpp"
#include "System/window.hpp"

#include <GLFW/glfw3.h>

KeyboardInput::KeyboardInput(GLFWwindow* window){
    glfwSetKeyCallback(window, KeyboardInput::GLFW_key_callback);
}
void KeyboardInput::EndFrame(){
    m_PreviousKeys = m_CurrentKeys;
}

bool KeyboardInput::IsKeyHeld(Key key) {
    return m_CurrentKeys.test(static_cast<size_t>(key));
}bool KeyboardInput::IsKeyPressed(Key key) {
    int k = static_cast<int>(key);
    return m_CurrentKeys.test(k) && !m_PreviousKeys.test(k);
}bool KeyboardInput::IsKeyReleased(Key key) {
    int k = static_cast<int>(key);
    return !m_CurrentKeys.test(k) && m_PreviousKeys.test(k);
}

// void KeyboardInput::Subscribe(Key key, EventCallback callback) {
//     m_Callbacks[key].push_back(callback);
// }

// The Static Bridge for polling
void KeyboardInput::GLFW_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Retrieve our Singleton instance from the window pointer
    KeyboardInput* instance = static_cast<EngineContext*>(glfwGetWindowUserPointer(window))->keyboard;
    //if (!KeyboardInput || key < 0 || key >= 512) return;

    if (key < 0 || key >= 512) return;

    if (action == GLFW_PRESS){
        instance->m_CurrentKeys.set(key);
        
        // if (KeyboardInput->m_Callbacks.count(engineKey)) {
        //     for (auto& func : KeyboardInput->m_Callbacks[engineKey]) {
        //         func();
        //     }
        // }
    } 
    else if(action == GLFW_RELEASE){
        instance->m_CurrentKeys.reset(key);
    }
}