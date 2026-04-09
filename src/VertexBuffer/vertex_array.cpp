#include "VertexBuffer/vertex_array.hpp"
#include <iostream>

#include <GL/glew.h>

#include "Geometry/vector2.hpp"
#include "VertexBuffer/vertex.hpp"
#include "VertexBuffer/stl.hpp"

void VertexArray::draw(){
    bind();
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    //glDrawElements(GL_TRIANGLES, vertices.size(), GL_UNSIGNED_INT, 0);
}


void VertexArray::bind(){
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
}

void VertexArray::gen_buffer(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    bind();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // glVertexAttribPointer(GLuint idx,GLuint size , GLenum type, GLenum normalised, GLuint stride, const coid* ptr);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // // Colour attribute
    // glVertexAttribPointer(2, 3, GL_UNSIGNED_INT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
    // glEnableVertexAttribArray(1);
}

void VertexArray::debug_print(){
    for(size_t i = 0;i<vertices.size();i++){
        std::cout<<"Vertex "<<i<<": "<<vertices[i].v[0]<<","<<vertices[i].v[1]<<","<<vertices[i].v[2]<<"\n";
        std::cout<<"Normal "<<i<<": "<<vertices[i].n[0]<<","<<vertices[i].n[1]<<","<<vertices[i].n[2]<<"\n";
    }
}

VertexArray::VertexArray(const char* file_path){
    STL::Mesh loader(file_path);
    vertices = std::move(loader.genVertices());

    gen_buffer();
}
VertexArray::~VertexArray(){
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1, &VBO);
}

