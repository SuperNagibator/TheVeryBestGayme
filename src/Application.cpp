#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

#include "Application.hpp"

struct WindowWrapper {
    GLFWwindow *window;

    WindowWrapper(int width, int height, const char *title) {
        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window) {
            throw std::runtime_error("window creation failed");
        }
    }

    ~WindowWrapper() {
        glfwDestroyWindow(window);
    }
};

Application::Application() {
    WindowWrapper windowWrapper(800, 600, "TheVeryBestGame");
    glfwMakeContextCurrent(windowWrapper.window);

    if (!gladLoadGL(glfwGetProcAddress)) {
        throw std::runtime_error("opengl loading failed");
    }

    while (!glfwWindowShouldClose(windowWrapper.window)) {
        glfwPollEvents();

        glClearColor(0.4, 0.6, 0.8, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(windowWrapper.window);
    }
}