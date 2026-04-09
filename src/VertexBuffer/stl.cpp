#include "VertexBuffer/stl.hpp"

#include "VertexBuffer/vertex.hpp"

#include <cstring>
#include <stdexcept>
#include <vector>
#include <iostream>

namespace STL{

bool Mesh::is_binary(std::ifstream& file){
    file.seekg(0, std::ios::end);
    std::streamsize fileSize = file.tellg();
        
    file.seekg(80, std::ios::beg);
    uint32_t expectedTriangles = 0;
    file.read(reinterpret_cast<char*>(&expectedTriangles), 4);

    std::streamsize expectedBinarySize = 84 + (static_cast<std::streamsize>(expectedTriangles)*50);

    file.clear();              // Clear any EOF or error flags
    file.seekg(0, std::ios::beg);

    if(expectedBinarySize == fileSize){
        return true;
    }else{
        return false;
    }
}

void Mesh::load_binary(std::ifstream& file){
    file.seekg(80, std::ios::beg);
    file.read(reinterpret_cast<char*>(&m_TriangleCount), 4);

    m_Triangles = new Triangle[m_TriangleCount];

    //Need to reed triangle by triangle as out triangles are 52 byte aligned, whlile they are 50 aligned
    for (size_t i = 0;i<m_TriangleCount;i++){
        char buffer[50];
        file.read(buffer, 50);

        memcpy(&m_Triangles[i], buffer, 50);
    }
}
void Mesh::load_ascii(std::ifstream& file) {
    std::string word;
    std::vector<Triangle> tempTriangles;

    // Skip the "solid <name>" header
    file >> word; // reads "solid"
    std::getline(file, word); // consumes the rest of the line (the name)

    while (file >> word) {
        if (word == "facet") {
            Triangle tri;
            file >> word; // reads "normal"
            
            // Read Normal Vector
            file >> tri.normal[0] >> tri.normal[1] >> tri.normal[2];

            file >> word; // reads "outer"
            file >> word; // reads "loop"

            // Read 3 Vertices
            for (int i = 0; i < 3; i++) {
                file >> word; // reads "vertex"
                file >> tri.v[i][0] >> tri.v[i][1] >> tri.v[i][2];
            }

            file >> word; // reads "endloop"
            file >> word; // reads "endfacet"

            tempTriangles.push_back(tri);
        } else if (word == "endsolid") {
            break;
        }
        // else comment
    }

    // Move data from the temporary vector to your raw array
    m_TriangleCount = static_cast<uint32_t>(tempTriangles.size());
    m_Triangles = new Triangle[m_TriangleCount];
    
    // Using memcpy since Triangle is POD (Plain Old Data)
    std::memcpy(m_Triangles, tempTriangles.data(), m_TriangleCount * sizeof(Triangle));
}
Mesh::Mesh(const char* filepath){
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open STL file");
    }
    if (is_binary(file)) {
        load_binary(file);
    } else {
        load_ascii(file);
    }

}

Mesh::~Mesh(){
    delete[] m_Triangles;
}
Mesh::Mesh(const Mesh& other){
    m_TriangleCount = other.m_TriangleCount;
    m_Triangles = new Triangle[m_TriangleCount];
    memcpy(m_Triangles, other.m_Triangles, m_TriangleCount * sizeof(Triangle));
}
Mesh& Mesh::operator=(const Mesh& other){
    if(this!=&other) {
        delete[] m_Triangles;
        m_TriangleCount = other.m_TriangleCount;
        m_Triangles = new Triangle[m_TriangleCount];
        memcpy(m_Triangles, other.m_Triangles, m_TriangleCount * sizeof(Triangle));
    }
    return *this;
}
Mesh::Mesh(Mesh&& other) noexcept : m_Triangles(other.m_Triangles), m_TriangleCount(other.m_TriangleCount) {
    other.m_Triangles = nullptr;
    other.m_TriangleCount = 0;
}
Mesh& Mesh::operator=(Mesh&& other) noexcept {
    if (this != &other) {
        delete[] m_Triangles;
        m_Triangles = other.m_Triangles;
        m_TriangleCount = other.m_TriangleCount;

        other.m_Triangles = nullptr;
        other.m_TriangleCount = 0;
    }
    return *this;
}


const Triangle* Mesh::getRaw() const{
    return m_Triangles;
}

std::vector<Vertex> Mesh::genVertices() const{
    std::vector<Vertex> out(m_TriangleCount*3);
    for(int i=0;i<m_TriangleCount;i++){
        auto get_vert = [&](int x){
            out[i*3+x] = Vertex{
                {m_Triangles[i].v[x][0],m_Triangles[i].v[x][1],m_Triangles[i].v[x][2]},
                {m_Triangles[i].normal[0],m_Triangles[i].normal[1],m_Triangles[i].normal[2]}
            };
        };
        get_vert(0);
        get_vert(1);
        get_vert(2);
    }
    return out;
}







void Mesh::debug_print() const{
    for(size_t i = 0;i<m_TriangleCount;i++){
        for(int j=0;j<3;j++){
            std::cout<<m_Triangles[i].normal[j]<<' ';
        }std::cout<<'\n';
        for(int x = 0;x<3;x++){
            for(int y=0;y<3;y++){
                std::cout<<m_Triangles[i].v[x][y]<<' ';
            }std::cout<<'\n';
        }std::cout<<"\n\n";
    }
}

}