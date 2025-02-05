#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

#include "Application.hpp"

Application::Application() {
    GLFWwindow *window = glfwCreateWindow(800, 600, "TheVeryBestGayme", nullptr, nullptr);
    if (!window) {
        throw std::runtime_error("window creation failed");
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGL(glfwGetProcAddress)) {
        throw std::runtime_error("opengl loading failed");
    }

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.4, 0.6, 0.8, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
}