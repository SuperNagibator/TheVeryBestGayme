#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <exception>
#include <iostream>

#include "Application.hpp"

int main() {
    if (!glfwInit()) {
        std::cerr << "error: glfw initialization failed\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    try {
        Application application;
    } catch (std::exception &e) {
        std::cerr << "error: " << e.what() << '\n';
    }

    glfwTerminate();

    return 0;
}