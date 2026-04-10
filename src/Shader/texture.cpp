#include "Shader/textue.hpp"


Texture::Texture(const char* file_path){
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);  

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char *data = stbi_load(file_path, &width, &height, &nrChannels, 0);
    if(data){
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //tells OpenGL not to expect padding at the end of each image row,
        //Chanels to tae care
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        std::cerr << "Failed to load texture:"<<file_path<<std::endl;
    }
    //set idx for uniform
    stbi_image_free(data);
}

Texture::~Texture(){
    glDeleteTextures(1, &ID);
}

void Texture::use() const{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ID);
}

int Texture::getWidth() const{
    return width;
}
int Texture::getHeight() const{
    return height;
}