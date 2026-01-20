#include "image/texture.h"
#include "image/image.h"

#include <GL/glew.h>

Texture::Texture(const Image& image):width(image.width), height(image.height), channels(image.channels){
    glGenTextures(1, &textureID);
    set_config();
    upload_data(image.data);
}

Texture::~Texture(){
    glDeleteTextures(1, &textureID);
}

void Texture::bind(){
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::set_config(){
    bind();
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
void Texture::upload_data(const unsigned char* data){
    bind();
    GLenum format = GL_RGB;
    if(channels == 1)
        format = GL_RED;
    else if(channels == 3)
        format = GL_RGB;
    else if(channels == 4)
        format = GL_RGBA;

    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //tells OpenGL not to expect padding at the end of each image row,
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::use(){
    glActiveTexture(GL_TEXTURE0);
    bind();
}