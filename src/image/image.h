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
    void debugmaker(){
        width=2;
        height=2;
        channels=4;
        //Pading end 0's which open gl expetcts by default //glPixelStorei(GL_UNPACK_ALIGNMENT, 1); to tell no padding needed
        data = new unsigned char[]{
            255,0,0,   0,255,0,0,0,
            0,0,255,   255,255,0,0,0
        };
    }
};

#endif