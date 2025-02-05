#include <glad/gl.h>

#include <vector>
#include <stdexcept>

#include "Shader.hpp"

GLuint createShader(const char *source, GLenum type) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

    if (!compileStatus) {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<char> infoLog(infoLogLength);
        glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog.data());

        throw std::runtime_error(infoLog.data());
    }

    return shader;
}

Shader::Shader(const char *vert, const char *frag) {
    GLuint vertShader = createShader(vert, GL_VERTEX_SHADER);
    GLuint fragShader = createShader(frag, GL_FRAGMENT_SHADER);

    program = glCreateProgram();

    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);

    glLinkProgram(program);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    GLint linkStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

    if (!linkStatus) {
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<char> infoLog(infoLogLength);
        glGetProgramInfoLog(program, infoLogLength, nullptr, infoLog.data());

        throw std::runtime_error(infoLog.data());
    }
}

Shader::~Shader() {
    glDeleteProgram(program);
}