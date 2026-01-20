#include <GL/glew.h>

#include "tilemap.h"
#include "buffer.h"

float vertices[] = {
        // ===== Front face (+Z) =====
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 0
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 1
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // 2
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // 3

        // ===== Back face (-Z) =====
        0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 4
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // 5
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 6
        0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 7

        // ===== Left face (-X) =====
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 8
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 9
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // 10
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 11

        // ===== Right face (+X) =====
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 12
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // 13
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 14
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // 15

        // ===== Bottom face (-Y) =====
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 16
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // 17
        0.5f, -0.5f,  0.5f,  1.0f, 1.0f, // 18
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, // 19

        // ===== Top face (+Y) =====
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // 20
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 21
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 22
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f  // 23
    };
    unsigned int indices[] = {
        // Front
        0, 1, 2,
        0, 2, 3,

        // Back
        4, 5, 6,
        4, 6, 7,

        // Left
        8, 9, 10,
        8, 10, 11,

        // Right
        12, 13, 14,
        12, 14, 15,

        // Bottom
        16, 17, 18,
        16, 18, 19,

        // Top
        20, 21, 22,
        20, 22, 23
    };

std::vector<glm::mat4> disp = {
    glm::mat4(1.0f),
    glm::rotate(glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f)),45.0f,glm::vec3(0.0f,1.0f,0.0f)),
    glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.0f, 0.0f))
};

void TileMap::bindVAO(){
    glBindVertexArray(VAO);
}void TileMap::unBindVAO(){
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
}
void TileMap::bindVBOs(){
    TileMap::bindVAO();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
   
    Buffer::AttributeSet_3_2(0);

    
    glBindBuffer(GL_ARRAY_BUFFER, instacesVBO);
    glBufferData(GL_ARRAY_BUFFER, disp.size()*sizeof(glm::mat4), disp.data(), GL_STATIC_DRAW);

    Buffer::AttributeSet_Mat4(4,true);


    TileMap::unBindVAO();
}

// ==================================================
//  Constructors
// ==================================================
TileMap::TileMap(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &instacesVBO);
    TileMap::bindVBOs();
}
TileMap::~TileMap(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1,&instacesVBO);
    //Texture Delted
}
 
void TileMap::setTexture(const Image& image){
    texture.loadFromImage(image);
}
void TileMap::draw(std::size_t instanceCount) const{
    texture.use();
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, instanceCount);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, 36);
}