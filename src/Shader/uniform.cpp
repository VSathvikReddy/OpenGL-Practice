#include <glm/glm.hpp>
#include "Geometry/vector3.hpp"
#include <GL/glew.h>

#include "uniform.hpp"

template<typename T>
Uniform<T>::Uniform(unsigned int shader_ID,const char* name){
    ID = glGetUniformLocation(shader_ID, name);
}
template<typename T>
Uniform<T>::Uniform(unsigned int shader_ID,const char* name,T v):Uniform(shader_ID,name){
    value = v;
}

template<typename T>
void Uniform<T>::setValue(T new_value){
    value = new_value;
    is_dirty = true;
}
template<typename T>
void Uniform<T>::update_shader(){
    if(is_dirty){
        sync_shader();
        is_dirty = false;
    }
}

template<>
void Uniform<bool>::sync_shader(){
    glUniform1i(ID, (int)value); 
}
template<>
void Uniform<int>::sync_shader(){
    glUniform1i(ID, value); 
}
template<>
void Uniform<float>::sync_shader(){
    glUniform1f(ID, value); 
}
template<>
void Uniform<glm::mat4>::sync_shader(){
    //                Loc,count,No Trans,Value 
    glUniformMatrix4fv(ID, 1, GL_FALSE, &value[0][0]); 
}
template<>
void Uniform<Vec3f>::sync_shader(){
    glUniform3f(ID, value[0], value[1], value[2]);
}