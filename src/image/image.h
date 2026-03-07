#ifndef IMAGE_H
#define IMAGE_H

class Image{
private:

public:
    int width = 0;
    int height = 0;
    int channels = 0;
    unsigned char* data = nullptr;
    
    Image(){}
    Image(const std::string& path);
    ~Image();

    bool loadImageFromFile(const std::string& path);
    bool saveImageToFile(const std::string& path);

    void flipVertical();
};

#endif