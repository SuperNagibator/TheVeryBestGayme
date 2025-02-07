#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
#include <memory>

#include "Application.hpp"
#include "Resource.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"

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

    Resource vertResource("resources/test.vert");
    std::vector<char> vert = vertResource.load();
    vert.push_back('\0');

    Resource fragResource("resources/test.frag");
    std::vector<char> frag = fragResource.load();
    frag.push_back('\0');

    std::vector<float> vertices = {
        0.0, 0.0,
        1.0, 0.0,
        0.0, 1.0,
    };

    std::vector<unsigned short> triangles = {
        0, 1, 2
    };

    std::shared_ptr<Shader> shader = std::make_shared<Shader>(vert.data(), frag.data());
    Mesh mesh(vertices, triangles, shader);

    while (!glfwWindowShouldClose(windowWrapper.window)) {
        glfwPollEvents();

        glClearColor(0.4, 0.6, 0.8, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        mesh.draw();

        glfwSwapBuffers(windowWrapper.window);
    }
}