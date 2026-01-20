#ifndef TILE_MAP
#define TILE_MAP

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "image.h"
#include "texture.h"
#include "buffer.h"

using mat4f = glm::mat4;

class TileMap{
private:
    Buffer::VAO vao;
    Buffer::VBO vbo,instacesvbo;
    Buffer::EBO ebo;

    int count;
    Texture texture;

    void unBind();
    void setData();
public:
    TileMap();
    ~TileMap();

    void setTexture(const Image& image);
    void sendInstanceData(int size, const void* data,GLenum usage = GL_DYNAMIC_DRAW);
    void draw() const;
};


#endif