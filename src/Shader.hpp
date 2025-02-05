#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/gl.h>

class Shader {
    GLuint program;

public:
    Shader(const char *vert, const char *frag);
    ~Shader();
};

#endif // SHADER_HPP