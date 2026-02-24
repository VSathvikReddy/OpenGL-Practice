#include "texture.h"
#include "image.h"

#include <GL/glew.h>

// ==================================================
//  Constructors
// ==================================================
Texture::Texture(){
    glGenTextures(1, &textureID);
    set_config();
}Texture::Texture(const Image& image):Texture(){
    loadFromImage(image);
}Texture::~Texture(){
    glDeleteTextures(1, &textureID);
}

// ==================================================
//  Private Functions
// ==================================================
void Texture::bind() const{
    glBindTexture(GL_TEXTURE_2D, textureID);
}
void Texture::set_config() const{
    Texture::bind();
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);  
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
}
void Texture::upload_data(const unsigned char* data) const{
    Texture::bind();
    GLenum format = GL_RGB;
    if(channels == 1)
        format = GL_RED;
    else if(channels == 3)
        format = GL_RGB;
    else if(channels == 4)
        format = GL_RGBA;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //tells OpenGL not to expect padding at the end of each image row,
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}
// ==================================================
//  Public Functions
// ==================================================
unsigned int Texture::getWidth() const{
    return width;
}unsigned int Texture::getHeight() const{
    return height;
}

bool Texture::loadFromImage(const Image& image){
    width = image.width;
    height = image.height;
    channels = image.channels;
    Texture::upload_data(image.data);
    return true;
}
void Texture::use() const {
    glActiveTexture(GL_TEXTURE0);
    Texture::bind();
}