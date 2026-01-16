#ifndef INIT_H
#define INIT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GLFWwindow GLFWwindow;

GLFWwindow* make_window();
void error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#ifdef __cplusplus
}
#endif

#endif