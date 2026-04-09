#include "System/engine_context.hpp"
#include "System/mouse_input.hpp"
#include "System/keyboard_input.hpp"
#include "System/window.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

EngineContext::EngineContext(Window* window_):window(window_){\
    GLFWwindow* native = window->GetNativeWindow();
    glfwSetWindowUserPointer(native, this);

    this->mouse = new MouseInput(native);
    this->keyboard = new KeyboardInput(native);
}  

EngineContext::~EngineContext(){
    delete mouse;
    delete keyboard;
}