#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/gl.h>

#include <cstdint>
#include <vector>

class Texture {
    GLuint texture;

public:
    Texture(std::vector<char> &data, uint32_t width, uint32_t height);
    ~Texture();

    void bind();
};

#endif // TEXTURE_HPP