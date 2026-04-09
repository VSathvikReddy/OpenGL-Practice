#pragma once


//Needs to be matched with a string
template<typename T>
class Uniform{
private:
    unsigned int ID=0;
    T value;
    bool is_dirty=true;

    void setValue(T new_value);
private:
    Uniform(unsigned int shader_ID, const char* name);
    Uniform(unsigned int shader_ID,const char* name,T v);

    void sync_shader();
    void update_shader();
};





