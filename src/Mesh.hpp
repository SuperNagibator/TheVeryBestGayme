#ifndef MESH_HPP
#define MESH_HPP

#include <glad/gl.h>

#include <vector>

class Mesh {
    GLuint vertexArray;
    GLuint vertexBuffer;
    GLuint triangleBuffer;
    GLsizei trianglesCount;

public:
    Mesh(std::vector<float> &vertices, std::vector<unsigned short> &triangles);
    ~Mesh();

    void draw();
};

#endif // MESH_HPP