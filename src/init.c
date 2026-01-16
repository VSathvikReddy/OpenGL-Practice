#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "init.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


GLFWwindow* make_window(){

    /* Initialize the library */
    if (!glfwInit()){
        fprintf(stderr, "glfw did not initialise properly\n");
        exit(1);
    }   
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    glfwSetErrorCallback(error_callback);


    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window){
        fprintf(stderr, "glfw window did not open properly\n");
        glfwTerminate();
        exit(1);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(glewInit() != GLEW_OK){
        fprintf(stderr, "glew did not initialise properlyy\n");
        exit(1);
    }

    printf("%s\n",glGetString(GL_VERSION));

    return window;
}



//Function called in case of error
void error_callback(int error, const char* description){
    fprintf(stderr, "Error: %s\n", description);
}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}