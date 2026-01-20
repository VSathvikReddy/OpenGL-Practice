#ifndef INIT_H
#define INIT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GLFWwindow GLFWwindow;

GLFWwindow* make_window();
void make_buffer(unsigned int* VBO,unsigned int* VAO, unsigned int* EBO,unsigned int* instacesVBO, float* vertices, int vsize, unsigned int* indices, int isize, float* disp, int dsize );
void error_callback(int error, const char* description);
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#ifdef __cplusplus
}
#endif

#endif