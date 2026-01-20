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
    Buffer::VBO vbo,instacesvbo, instaceTexturevbo;
    Buffer::EBO ebo;

    int count;
    

    void unBind();
    void layoutAttributes();
public:
    Texture texture;

    TileMap();
    TileMap(const std::vector<float>& vertices,const std::vector<unsigned int>& indices,const std::vector<float>& texoff,const std::string& address);
    ~TileMap();

    void setTexture(const Image& image);
    void sendStaticData(const std::vector<float>& vertices,const std::vector<unsigned int>& indices,const std::vector<float>& texoff,const std::string& address);

    void sendInstanceData(int size, const void* data);
    void draw() const;
};


#endif