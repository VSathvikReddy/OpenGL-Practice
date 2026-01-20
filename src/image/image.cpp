#include <iostream>
#include <fstream>
#include <limits>

#include "image.h"

#include <cstring>
#include <vector>

// ==================================================
//  Constructors
// ==================================================
Image::Image(const std::string& path){
    loadImageFromFile(path);
}
Image::~Image(){
    if(this->data)
        delete[] (this->data);
}
void Image::flipVertical(){
    int rowSize = this->width * 3;
    std::vector<unsigned char> temp(rowSize);

    for(int y=0;y<this->height/2;y++){
        unsigned char* row1 = this->data + y * rowSize;
        unsigned char* row2 = this->data + (this->height - 1 - y) * rowSize;

        memcpy(temp.data(), row1, rowSize);
        memcpy(row1, row2, rowSize);
        memcpy(row2, temp.data(), rowSize);
    }
}

bool Image::loadImageFromFile(const std::string& path){
    if(this->data){ delete [] this->data;data = nullptr;}
    std::ifstream file(path, std::ios::binary);
    if(!file.is_open()){
        std::cerr << "Failed to open PPM file: " << path << std::endl;
        return false;
    }
    auto skip_comments = [&](std::ifstream& f) {
        while (f.peek() == '#') {
            f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    };
    std::string format;
    file >> format;
    if(format != "P6"){
        std::cerr << "Unsupported PPM format: " << format << std::endl;
        return false;
    }skip_comments(file);

    int maxColorValue;
    file >> this->width >> this->height >> maxColorValue;
    if(maxColorValue != 255){
        std::cerr<<"Only 8-bit PPM supported:"<<path<<std::endl;
        return false;
    }
    skip_comments(file);
    file.get(); // consume the newline character after maxColorValue
    this->data = new unsigned char[this->width * this->height * 3];
    file.read(reinterpret_cast<char*>(this->data), this->width * this->height * 3);
    if(!file){
        std::cerr << "Error reading PPM pixel data from file: " << path <<std::endl;
        delete[] this->data;
        this->width = 0;this->height = 0;this->channels = 0;
        return false;
    }
    Image::flipVertical();
    return true;
}

bool Image::saveImageToFile(const std::string& path){
    Image::flipVertical();
    std::ofstream file(path, std::ios::binary);
    if(!file.is_open()){
        std::cerr << "Failed to open PPM file for writing: " << path << std::endl;
        Image::flipVertical();
        return false; 
    }
    file << "P6\n" << width << " " << height << "\n255\n";
    file.write(reinterpret_cast<char*>(data), width * height * 3);
    if(!file){
        std::cerr << "Error writing PPM pixel data to file: " << path << std::endl;
        Image::flipVertical();
        return false;
    }
    Image::flipVertical();
    return true;
}