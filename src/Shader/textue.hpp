#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glew.h>

#include <iostream>
#include <cstdint>

class Texture{
public:
    Texture(const char* file_path);
    ~Texture();

    int getWidth() const;
    int getHeight() const;

    void use() const;
private:
    uint32_t ID;
    int width, height, nrChannels;
};