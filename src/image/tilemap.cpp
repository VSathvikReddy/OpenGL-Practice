#include <GL/glew.h>

#include "tilemap.h"
#include "buffer.h"

std::vector<float> vertices = {
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
    std::vector<unsigned int> indices = {
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


// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
//Buffer::VBO::unbind();

// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
//Buffer::VBO::unbind();

void TileMap::unBind(){
    Buffer::VBO::unbind();
    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    Buffer::VAO::unbind();
}
void TileMap::setData(){
    vao.bind();
    vbo.sendData(vertices.size()*sizeof(float),vertices.data());
    Buffer::AttributeSet_3_2(0);

    ebo.sendData(indices.size()*sizeof(unsigned int), indices.data());
    
    count = disp.size();
    instacesvbo.sendData(disp.size()*sizeof(glm::mat4),disp.data());
    Buffer::AttributeSet_Mat4(4,true);

    texture.loadFromImage(Image("test.ppm"));
    TileMap::unBind();
}

// ==================================================
//  Constructors
// ==================================================
TileMap::TileMap(){
    TileMap::setData();
}
TileMap::~TileMap(){
}
 
void TileMap::setTexture(const Image& image){
    texture.loadFromImage(image);
}
void TileMap::draw() const{
    texture.use();
    vao.bind();
    ebo.bind();
    glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, count);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, 36);
}