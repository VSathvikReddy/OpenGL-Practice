#include <GL/glew.h>

#include "tilemap.h"
#include "buffer.h"

// ==================================================
//  Private Functions
// ==================================================
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
void TileMap::layoutAttributes(){
    vao.bind();
    vbo.bind();
    Buffer::AttributeSet_3_2(0);
    instacesvbo.bind();
    Buffer::AttributeSet_Mat4(4,true);
    instaceTexturevbo.bind();
    Buffer::AttributeSet_Vec2(2,true);
}
// ==================================================
//  Constructors
// ==================================================
TileMap::TileMap(){
    TileMap::layoutAttributes();
}
TileMap::TileMap(const std::vector<float>& vertices,const std::vector<unsigned int>& indices,const std::vector<float>& texoff,const std::string& address){
    vao.bind();
    vbo.sendData(vertices.size()*sizeof(float),vertices.data(),GL_STATIC_DRAW);
    Buffer::AttributeSet_3_2(0);
    ebo.sendData(indices.size()*sizeof(unsigned int), indices.data(),GL_STATIC_DRAW);
    instacesvbo.bind();
    Buffer::AttributeSet_Mat4(4,true);
    instaceTexturevbo.sendData(indices.size()*sizeof(float),texoff.data(),GL_STATIC_DRAW);
    Buffer::AttributeSet_Vec2(2,true);
    
    texture.loadFromImage(Image(address));
    TileMap::unBind();
}
TileMap::~TileMap(){
}
 
// ==================================================
//  Public Functions
// ==================================================

// ===========================================
//  Sending Data
// ===========================================
void TileMap::sendStaticData(const std::vector<float>& vertices,const std::vector<unsigned int>& indices,const std::vector<float>& texoff,const std::string& address){
    vao.bind();

    vbo.sendData(vertices.size()*sizeof(float),vertices.data(),GL_STATIC_DRAW);
    ebo.sendData(indices.size()*sizeof(unsigned int), indices.data(),GL_STATIC_DRAW);
    instaceTexturevbo.sendData(indices.size()*sizeof(float),texoff.data(),GL_STATIC_DRAW);

    texture.loadFromImage(Image(address));
    TileMap::unBind();
}
void TileMap::sendInstanceData(int size, const void* data){
    vao.bind();
    count = size;
    instacesvbo.sendData(size,data,GL_DYNAMIC_DRAW);
}
void TileMap::setTexture(const Image& image){
    texture.loadFromImage(image);
}
// ==================================================
//  Using Data
// ==================================================
void TileMap::draw() const{
    texture.use();
    vao.bind();
    ebo.bind();
    glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, count);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, 36);
}