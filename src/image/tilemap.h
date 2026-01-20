#ifndef TILE_MAP
#define TILE_MAP

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "image.h"
#include "texture.h"
#include "buffer.h"

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
    void setInstances(const std::vector<glm::mat4>& transforms);

    void draw() const;
};


#endif