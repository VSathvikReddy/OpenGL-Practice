#include <string>
#include <cstdio>
#include <cstdlib>

#include "shader.h"


//Changes to be made
char* file_read(const std::string& path){
    FILE* f = fopen(path.c_str(), "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char* buffer = (char*)malloc(size + 1);
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

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath){
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


void Shader::setBool(const std::string &name, bool value) const{         
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}void Shader::setInt(const std::string &name, int value) const{ 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}void Shader::setFloat(const std::string &name, float value) const{ 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}void Shader::setMat4(const std::string &name, const float* value) const{ 
    //                  Where                             How many, No Trans, Value 
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value); 
} 