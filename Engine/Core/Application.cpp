#include <glad/glad.h>            // ✅ Must come before glfw
#include <GLFW/glfw3.h>           // Window/input

#include "Application.h"
#include "../Input/Input.h"
#include "../Lua/ScriptSystem.h"

// Graphics
#include "../Graphics/Camera.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Mesh.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Skybox.h"

// ImGui
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>
#include <glm/glm.hpp>

namespace Engine {

    Application::Application() {
        std::cout << "[Engine] Constructing Application...\n";
    }

    void Application::Run() {
        // GLFW Init
        if (!glfwInit()) {
            std::cerr << "[GLFW] Initialization failed.\n";
            return;
        }

        // Create window
        GLFWwindow* window = glfwCreateWindow(800, 600, "SoulsEngine", nullptr, nullptr);
        if (!window) {
            std::cerr << "[GLFW] Window creation failed.\n";
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // VSync

        // Load OpenGL functions with glad
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "[Glad] Failed to initialize OpenGL context\n";
            return;
        }

        std::cout << "[Engine] OpenGL loaded: " << glGetString(GL_VERSION) << "\n";

        // Enable depth test for 3D
        glEnable(GL_DEPTH_TEST);

        // Setup input system
        Input::Init(window);

        // Initialize Lua scripting
        InitLua();

        // Setup ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        // Setup camera
        Camera camera(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
        camera.SetPosition({ 0.0f, 0.0f, 3.0f });

        // Load shaders, mesh, and skybox
        Shader shader("Game/Shaders/basic.vert", "Game/Shaders/basic.frag");
        Shader skyboxShader("Game/Shaders/skybox.vert", "Game/Shaders/skybox.frag");
        Mesh mesh;
        Renderer renderer;
        Engine::Skybox skybox;

        // Main loop
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();

            if (Input::IsKeyPressed(GLFW_KEY_ESCAPE)) {
                glfwSetWindowShouldClose(window, true);
            }

            // Start ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // ImGui Debug UI
            ImGui::Begin("Engine Debug");
            ImGui::Text("SoulsEngine running...");
            ImGui::End();

            // Clear screen
            glViewport(0, 0, 800, 600);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black, skybox will cover
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Draw skybox first
            glm::mat4 view = camera.GetViewMatrix();
            glm::mat4 proj = camera.GetProjectionMatrix();
            glm::mat4 skyboxView = glm::mat4(glm::mat3(view)); // Remove translation
            glm::mat4 viewProj = proj * skyboxView;
            skybox.Draw(skyboxShader, viewProj);

            // Draw mesh with camera
            viewProj = proj * view;
            renderer.DrawMesh(mesh, shader, viewProj);

            // Render ImGui
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
        }

        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(window);
        glfwTerminate();
        std::cout << "[Engine] Shutdown complete.\n";
    }

}
