#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/gl.h>

class Shader {
    GLuint program;

public:
    Shader(const char *vert, const char *frag);
    ~Shader();

    void use();
};

#endif // SHADER_HPP