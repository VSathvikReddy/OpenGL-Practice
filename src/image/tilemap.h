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
    
    unsigned int VBO, VAO, EBO,instacesVBO;
    Texture texture;

    void bindVAO();
    void bindVBOs();
    void unBindVAO();
public:
    TileMap();
    ~TileMap();

    void setTexture(const Image& image);
    void setInstances(const std::vector<glm::mat4>& transforms);

    void draw(std::size_t instanceCount) const;
};


#endif