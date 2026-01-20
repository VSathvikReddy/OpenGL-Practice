#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define DEFAULT_VERTEX_SHADER "shaders/basic.vert"
#define DEFAULT_FRAGMENT_SHADER "shaders/basic.frag"
#define TILEMAP_VERTEX_SHADER "shaders/tilemap.vert"

char* file_read(const std::string& path);

class Shader{
private:
    unsigned int ID = 0;
    unsigned int createShader(GLenum type, const char* ShaderSource, char* infoLog);
    unsigned int linkShaders(unsigned int vertexShader, unsigned int fragmentShader, char* infoLog);
public:
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    ~Shader();
    Shader(const Shader&) = delete;             // no copying
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&& other) noexcept;      // move support

    // utility uniform functions
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setMat4(const std::string &name, const float* value) const;

    void use();
    unsigned int getID() const;
};

#endif