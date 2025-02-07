#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <spng.h>

#include <stdexcept>
#include <vector>
#include <memory>

#include "Application.hpp"
#include "Resource.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
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
        createWindow(800, 600, PROJECT_NAME), 
        glfwDestroyWindow
    );

    glfwMakeContextCurrent(window.get());

    if (!gladLoadGL(glfwGetProcAddress)) {
        throw std::runtime_error("opengl loading failed");
    }

    std::unique_ptr<spng_ctx, void(*)(spng_ctx*)> spngContext(
        spng_ctx_new(0),
        spng_ctx_free
    );

    Resource vertResource("resources/test.vert");
    std::vector<char> vert = vertResource.load();
    vert.reserve(vert.size() + 1);
    vert.push_back('\0');

    Resource fragResource("resources/test.frag");
    std::vector<char> frag = fragResource.load();
    vert.reserve(vert.size() + 1);
    frag.push_back('\0');

    Resource image("resources/test.png");
    std::vector<char> imagePng = image.load();
    spng_set_png_buffer(spngContext.get(), imagePng.data(), imagePng.size());

    size_t imageRawSize;
    spng_decoded_image_size(spngContext.get(), SPNG_FMT_RGBA8, &imageRawSize);

    std::vector<char> imageRaw(imageRawSize);
    spng_decode_image(spngContext.get(), imageRaw.data(), imageRawSize, SPNG_FMT_RGBA8, 0);

    spng_ihdr imageHeader;
    spng_get_ihdr(spngContext.get(), &imageHeader);
    std::shared_ptr<Texture> texture = std::make_shared<Texture>(imageRaw, imageHeader.width, imageHeader.height);

    std::vector<float> vertices = {
        -0.5, -0.5, 0.0, 1.0,
        0.5, -0.5, 1.0, 1.0,
        -0.5, 0.5, 0.0, 0.0,
        0.5, 0.5, 1.0, 0.0,
    };

    std::vector<unsigned short> triangles = {
        0, 1, 2,
        3, 2, 1,
    };

    std::shared_ptr<Shader> shader = std::make_shared<Shader>(vert.data(), frag.data());
    Mesh mesh(vertices, triangles, shader, texture);

    while (!glfwWindowShouldClose(window.get())) {
        glfwPollEvents();

        glClearColor(0.4, 0.6, 0.8, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        mesh.draw();

        glfwSwapBuffers(window.get());
    }
}