#ifndef INIT_H
#define INIT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GLFWwindow GLFWwindow;


void make_buffer(unsigned int* VBO,unsigned int* VAO, unsigned int* EBO, float* vertices, int vsize, unsigned int* indices, int isize );
void bind_texture(unsigned int* texture);

#ifdef __cplusplus
}
#endif

#endif