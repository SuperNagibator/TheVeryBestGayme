#include <GLFW/glfw3.h>

int main() {
    glfwInit();

    GLFWwindow *window = glfwCreateWindow(800, 600, "TheVeryBestGayme", nullptr, nullptr);
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}