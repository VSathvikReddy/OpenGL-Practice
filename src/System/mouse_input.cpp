#include "System/mouse_input.hpp"
#include "System/window.hpp"
#include "System/engine_context.hpp"

#include <GLFW/glfw3.h>

MouseInput::MouseInput(GLFWwindow* window){
    glfwSetCursorPosCallback(window, MouseInput::GLFW_mouse_callback);

    glfwGetCursorPos(window, &m_State.X, &m_State.Y);
    m_State.prevX = m_State.X;
    m_State.prevY = m_State.Y;
}
void MouseInput::EndFrame(){
    m_State.prevX = m_State.X;
    m_State.prevY = m_State.Y;
}



void MouseInput::GLFW_mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    MouseInput* instance = (static_cast<EngineContext*>(glfwGetWindowUserPointer(window)))->mouse;
    instance->m_State.X = xpos;
    instance->m_State.Y = ypos;
}