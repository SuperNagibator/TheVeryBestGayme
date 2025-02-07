#ifndef MESH_HPP
#define MESH_HPP

#include <glad/gl.h>

#include <vector>
#include <memory>

#include "Shader.hpp"
#include "Texture.hpp"

class Mesh {
    GLuint vertexArray;
    GLuint vertexBuffer;
    GLuint triangleBuffer;
    GLsizei trianglesCount;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<Texture> texture;

public:
    Mesh(
        std::vector<float> &vertices, 
        std::vector<unsigned short> &triangles, 
        std::shared_ptr<Shader> shader, 
        std::shared_ptr<Texture> texture
    );
    
    ~Mesh();

    void draw();
};

#endif // MESH_HPP