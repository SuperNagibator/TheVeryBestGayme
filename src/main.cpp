#include <glad/gl.h>
#include <GLFW/glfw3.h>

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "TheVeryBestGayme", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.4, 0.6, 0.8, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}