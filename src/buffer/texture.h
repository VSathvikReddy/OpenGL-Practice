#ifndef TEXTURE_H
#define TEXTURE_H


class Image; // Forward declaration

class Texture{
private:
    unsigned int textureID;
    unsigned int width, height, channels;

    void bind() const;
    void set_config() const;
    void upload_data(const unsigned char* data) const;
public:
    Texture();
    Texture(const Image& image);
    ~Texture();

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    bool loadFromImage(const Image& image);

    void use() const;
};

#endif
