#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include <GL/glew.h>

namespace Buffer{



class VAO{
private:
    unsigned int ID;
public:
    VAO();
    ~VAO();
    void bind();
    static void unbind();
};

class VBO{
private:
    unsigned int ID;
public:
    VBO();
    ~VBO();
    void bind();
    static void unbind();

    void sendData(std::vector<float> vertices,GLenum usage=GL_STATIC_DRAW);
};


void AttributeSet_3_2(int iniLayout = 0,bool instance = false);
void AttributeSet_Vec4(int iniLayout, bool instance);
void AttributeSet_Mat4(int iniLayout, bool instance=false);

}


#endif