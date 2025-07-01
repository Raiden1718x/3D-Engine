#pragma once
#include <GLFW/glfw3.h>
#include <vector>

namespace Engine {
    class Input {
    public:
        static void Init(GLFWwindow* window);
        static bool IsKeyPressed(int key);
        static void GetMousePosition(double& x, double& y);
        static int GetKeyPressed();
        static std::vector<int> GetPressedKeys(); // NEW
    private:
        static GLFWwindow* s_Window;
    };
}
