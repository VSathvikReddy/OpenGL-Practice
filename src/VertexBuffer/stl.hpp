#pragma once

#include <cstddef>
#include <fstream>
#include <vector>

struct Vertex;

namespace STL{

struct Triangle{
    float normal[3] = {0.0f, 0.0f, 0.0f};
    float v[3][3] = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}};
    uint16_t  attribute_byte_count =0;
};

class Mesh{
private:
    Triangle* m_Triangles = nullptr;
    size_t m_TriangleCount = 0;

    bool is_binary(std::ifstream& file);
    void load_binary(std::ifstream& file);
    void load_ascii(std::ifstream& file);
public:
    Mesh(const char* filepath);
    ~Mesh();

    Mesh(const Mesh& other);
    Mesh& operator=(const Mesh& other);

    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;

    void debug_print() const;
    const Triangle* getRaw() const;

    std::vector<Vertex> genVertices() const;
    size_t getTriangleCount() const;
};


}