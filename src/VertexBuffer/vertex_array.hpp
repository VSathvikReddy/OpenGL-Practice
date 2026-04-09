#pragma once

#include <vector>

struct Vertex;


class VertexArray{
public:
    VertexArray();
    VertexArray(const char* file_path);
    ~VertexArray();



    void bind();
    void gen_buffer();

    void draw();

    void debug_print();
private:
    unsigned int VAO=0;
    unsigned int VBO=0;
    std::vector<Vertex> vertices;

};