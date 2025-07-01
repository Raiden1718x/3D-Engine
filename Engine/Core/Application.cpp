#include "Application.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "../Lua/ScriptSystem.h"

namespace Engine {

    Application::Application() {
        std::cout << "[Engine] Constructing Application...\n";
    }

    void Application::Run() {
        // Initialize GLFW
        if (!glfwInit()) {
            std::cerr << "[GLFW] Initialization failed.\n";
            return;
        }

        // Create Window
        GLFWwindow* window = glfwCreateWindow(800, 600, "SoulsEngine", nullptr, nullptr);
        if (!window) {
            std::cerr << "[GLFW] Window creation failed.\n";
            glfwTerminate();
            return;
        }

        // Set OpenGL context
        glfwMakeContextCurrent(window);
        std::cout << "[Engine] GLFW Window created.\n";

        // Initialize Lua scripting
        InitLua();

        // Main loop
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();

            // Clear screen
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Swap buffers
            glfwSwapBuffers(window);
        }

        // Cleanup
        glfwDestroyWindow(window);
        glfwTerminate();
        std::cout << "[Engine] Shutdown complete.\n";
    }

}
