#include <GLFW/glfw3.h>


#include <stdlib.h>
#include <stdio.h>
#include <math.h>

GLFWwindow* make_window(){
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()){
        exit(1);
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window){
        glfwTerminate();
        exit(1);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    return window;
}

struct Vertex2f{
    float x;
    float y;

    Vertex2f():x(0.0f),y(0.0f){}
    Vertex2f(float _x, float _y):x(_x),y(_y){}

    Vertex2f rotate(float theta = 0.0f){
        float s = std::sin(theta);
        float c = std::cos(theta);

        return {
            x * c - y * s,
            x * s + y * c
        };
    }
};


inline void glVertex2f(const Vertex2f& v) {
    glVertex2f(v.x, v.y);
}


int main(){

    GLFWwindow* window = make_window();
    
    Vertex2f a(0.0f, 0.5f);
    Vertex2f b(0.5f, -0.5f);
    Vertex2f c(-0.5f, -0.5f);
    float angle = 0.0f;

    /* Loop until the user closes the window */
    while(!glfwWindowShouldClose(window)){
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(a.rotate(angle));
        glVertex2f(b.rotate(angle));
        glVertex2f(c.rotate(angle));
        glEnd();

        angle += 0.001f;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}