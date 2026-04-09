#include <string>
#include <cstdio>
#include <cstdlib>

#include "Shader/shader.hpp"

//Changes to be made
char* file_read(const char* path){
    FILE* f = fopen(path, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char* buffer = static_cast<char*>(malloc(size + 1));
    if (!buffer) {
        fclose(f);
        return NULL;
    }

    fread(buffer, 1, size, f);
    fclose(f);

    buffer[size] = '\0';
    return buffer;
}

unsigned int Shader::createShader(GLenum type, const char* ShaderSource, char* infoLog){
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int Shader = glCreateShader(type);
    glShaderSource(Shader, 1, &ShaderSource, NULL);
    glCompileShader(Shader);
    // check for shader compile errors

    int success;
    glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(Shader, 512, NULL, infoLog);
        const char* shaderType =(type == GL_VERTEX_SHADER) ? "VERTEX" :(type == GL_FRAGMENT_SHADER) ? "FRAGMENT" :"UNKNOWN";
        printf("ERROR::SHADER::%s::COMPILATION_FAILED\n%s\n", shaderType, infoLog);
    }

    return Shader;
}
unsigned int Shader::linkShaders(unsigned int vertexShader, unsigned int fragmentShader, char* infoLog){
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }
    return shaderProgram;
}

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath){
    char* vertexShaderSource = file_read(vertexShaderPath);
    char* fragmentShaderSource = file_read(fragmentShaderPath);
    if(!vertexShaderSource || !fragmentShaderSource){
        fprintf(stderr,"ERROR::SHADER::FILE_NOT_READ\n");
        if(!vertexShaderSource){fprintf(stderr,"Vertex\n");}
        if(!fragmentShaderSource){fprintf(stderr,"Fragment\n");}
        return;
    }
    char infoLog[512];
    unsigned int vertexShaderID = Shader::createShader(GL_VERTEX_SHADER, vertexShaderSource, infoLog);
    unsigned int fragmentShaderID = Shader::createShader(GL_FRAGMENT_SHADER, fragmentShaderSource, infoLog);

    this->ID = Shader::linkShaders(vertexShaderID, fragmentShaderID, infoLog);

    free(vertexShaderSource);
    free(fragmentShaderSource);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}
Shader::Shader(Shader&& other) noexcept{
        ID = other.ID;
        other.ID = 0;
}
Shader::~Shader(){
    glDeleteProgram(this->ID);
}

void Shader::use(){
    if(ID!=0) glUseProgram(ID);
}
unsigned int Shader::getID() const{
    return ID;
}



