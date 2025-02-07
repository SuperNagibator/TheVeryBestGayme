#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
#include <memory>

#include "Application.hpp"
#include "Resource.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"

GLFWwindow *createWindow(int width, int height, const char *title) {
    GLFWwindow *window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        throw std::runtime_error("window creation failed");
    }

    return window;
}

Application::Application() {
    std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)> window(
        createWindow(800, 600, "TheVeryBestGame"), 
        glfwDestroyWindow
    );

    glfwMakeContextCurrent(window.get());

    if (!gladLoadGL(glfwGetProcAddress)) {
        throw std::runtime_error("opengl loading failed");
    }

    Resource vertResource("resources/test.vert");
    std::vector<char> vert = vertResource.load();
    vert.reserve(vert.size() + 1);
    vert.push_back('\0');

    Resource fragResource("resources/test.frag");
    std::vector<char> frag = fragResource.load();
    vert.reserve(vert.size() + 1);
    frag.push_back('\0');

    std::vector<float> vertices = {
        -0.5, -0.5,
        0.5, -0.5,
        -0.5, 0.5,
        0.5, 0.5,
    };

    std::vector<unsigned short> triangles = {
        0, 1, 2,
        3, 2, 1,
    };

    std::shared_ptr<Shader> shader = std::make_shared<Shader>(vert.data(), frag.data());
    Mesh mesh(vertices, triangles, shader);

    while (!glfwWindowShouldClose(window.get())) {
        glfwPollEvents();

        glClearColor(0.4, 0.6, 0.8, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        mesh.draw();

        glfwSwapBuffers(window.get());
    }
}