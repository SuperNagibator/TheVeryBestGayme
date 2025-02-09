#include <glad/gl.h>

#include <vector>
#include <memory>

#include "Shader.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"

Mesh::Mesh(
    std::vector<float> &vertices, 
    std::vector<unsigned short> &triangles, 
    std::shared_ptr<Shader> shader,
    std::shared_ptr<Texture> texture
) : shader(shader), texture(texture) {
    glCreateVertexArrays(1, &vertexArray);
    glCreateBuffers(1, &vertexBuffer);
    glCreateBuffers(1, &triangleBuffer);

    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleBuffer);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(unsigned short), triangles.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void*>(0 * sizeof(float)));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));

    trianglesCount = triangles.size();
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &triangleBuffer);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &vertexArray);
}

void Mesh::draw() {
    shader->use();

    glActiveTexture(GL_TEXTURE0);
    texture->bind();

    glBindVertexArray(vertexArray);
    glDrawElements(GL_TRIANGLES, trianglesCount, GL_UNSIGNED_SHORT, 0);
}