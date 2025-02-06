#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
#include <memory>

#include "Application.hpp"
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

    const char *vert =
        "#version 460 core\n"
        "layout(location = 0) in vec2 in_position;\n"
        "void main() {\n"
        "   gl_Position = vec4(in_position, 0.0, 1.0);\n"
        "}\n"
        "\0";

    const char *frag =
        "#version 460 core\n"
        "layout(location = 0) out vec4 out_color;\n"
        "void main() {\n"
        "   out_color = vec4(0.8, 0.6, 0.4, 1.0);\n"
        "}\n"
        "\0";
    
    std::vector<float> vertices = {
        0.0, 0.0,
        1.0, 0.0,
        0.0, 1.0,
    };

    std::vector<unsigned short> triangles = {
        0, 1, 2
    };

    std::shared_ptr<Shader> shader = std::make_shared<Shader>(vert, frag);
    Mesh mesh(vertices, triangles, shader);

    while (!glfwWindowShouldClose(windowWrapper.window)) {
        glfwPollEvents();

        glClearColor(0.4, 0.6, 0.8, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        mesh.draw();

        glfwSwapBuffers(windowWrapper.window);
    }
}