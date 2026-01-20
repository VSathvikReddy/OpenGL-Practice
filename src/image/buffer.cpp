#include "buffer.h"
#include <glm/glm.hpp>

namespace Buffer{

VAO::VAO(){
    glGenVertexArrays(1, &ID);
}
VAO::~VAO(){
    glDeleteVertexArrays(1, &ID);
}
void VAO::bind(){
    glBindVertexArray(ID);
}
void VAO::unbind(){
    glBindVertexArray(0);
}

VBO::VBO(){
    glGenBuffers(1, &ID);
}

VBO::~VBO(){
    glDeleteBuffers(1, &ID);
}

void VBO::bind(){
    //Must be called only after array is bound
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void VBO::unbind(){
    //Must be called only after array is bound
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::sendData(std::vector<float> vertices,GLenum usage){
    VBO::bind();
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), usage);
}



void AttributeSet_3_2(int iniLayout, bool instance){

    glVertexAttribPointer(iniLayout, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(iniLayout);

    glVertexAttribPointer(iniLayout+1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(iniLayout+1);  

    if(instance){
        glVertexAttribDivisor(iniLayout, 1);
        glVertexAttribDivisor(iniLayout+1, 1);
    }
}

void AttributeSet_Vec4(int iniLayout, bool instance){
    glVertexAttribPointer(iniLayout, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(iniLayout);
    if(instance){
        glVertexAttribDivisor(iniLayout, 1);
    }

}
void AttributeSet_Mat4(int iniLayout, bool instance){
    for(int i=0;i<4;i++){
        glVertexAttribPointer(iniLayout+i,4,GL_FLOAT,GL_FALSE,sizeof(glm::mat4),(void*)(i * sizeof(glm::vec4)));
        glEnableVertexAttribArray(iniLayout+ i);
        if(instance){
            glVertexAttribDivisor(iniLayout+ i, 1);
        }
    }
}


}




