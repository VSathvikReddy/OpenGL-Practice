#include "System/window.hpp"
#include "System/engine_context.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void init_glfw(void (*error_function)(int, const char*) ){
    glfwSetErrorCallback(error_function);

    /* Initialize the library */
    if (glfwInit()!=GLFW_TRUE){
        fprintf(stderr, "glfw did not initialise properly\n");
        exit(1);
    } 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}
void init_glew(){
    GLenum GLsucess = glewInit();
    if(GLsucess != GLEW_OK){
        fprintf(stderr, "GLEW Initialization Error: %s\n",glewGetErrorString(GLsucess));
        exit(1);
    }
    glEnable(GL_DEPTH_TEST);  

    printf("%s\n",glGetString(GL_VERSION));
}
Window::Window(const WindowProperties& properties):m_Properties(properties){
    init_glfw(GLFW_error_callback);

    /* Create a windowed mode window and its OpenGL context */
    m_Window = glfwCreateWindow(properties.width, properties.height, properties.title, NULL, NULL);
    if (!m_Window){
        fprintf(stderr, "glfw window did not open properly\n");
        glfwTerminate();
        exit(1);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_Window);
    glfwSetFramebufferSizeCallback(m_Window, GLFW_framebuffer_size_callback);

    init_glew();
}

Window::~Window(){
    if (m_Window){
        glfwDestroyWindow(m_Window);
    }
    glfwTerminate();     // glfw: terminate, clearing all previously allocated GLFW resources.
}


GLFWwindow* Window::GetNativeWindow() const {
    return m_Window;
}

void Window::GLFW_error_callback(int error, const char* description){
    fprintf(stderr, "GLFW Error: %s\n", description);
}
void Window::GLFW_framebuffer_size_callback(GLFWwindow* window, int width, int height){
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);

    EngineContext* instance = static_cast<EngineContext*>(glfwGetWindowUserPointer(window));
    if(instance){
        instance->window->m_Properties.width = width;
        instance->window->m_Properties.width = height;
    }
}
