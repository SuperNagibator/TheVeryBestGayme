#ifndef MESH_HPP
#define MESH_HPP

#include <glad/gl.h>

#include <vector>
#include <memory>

#include "Shader.hpp"

class Mesh {
    GLuint vertexArray;
    GLuint vertexBuffer;
    GLuint triangleBuffer;
    GLsizei trianglesCount;
    std::shared_ptr<Shader> shader;

public:
    Mesh(std::vector<float> &vertices, std::vector<unsigned short> &triangles, std::shared_ptr<Shader> shader);
    ~Mesh();

    void draw();
};

#endif // MESH_HPP