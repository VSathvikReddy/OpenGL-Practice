class Image; // Forward declaration

class Texture{
private:
    unsigned int textureID;
    int width, height, channels;

    void bind();
    void set_config();
    void upload_data(const unsigned char* data);
public:
    Texture(const Image& image);
    ~Texture();

    void use();
};


