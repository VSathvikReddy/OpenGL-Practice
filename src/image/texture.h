#ifndef TEXTURE_H
#define TEXTURE_H


class Image; // Forward declaration

class Texture{
private:
    unsigned int textureID;
    int width, height, channels;

    void bind() const;
    void set_config();
    void upload_data(const unsigned char* data);
public:
    Texture();
    Texture(const Image& image);
    ~Texture();

    bool loadFromImage(const Image& image);

    void use() const;
};

#endif
