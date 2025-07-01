#include "Input.h"

namespace Engine {
    GLFWwindow* Input::s_Window = nullptr;

    void Input::Init(GLFWwindow* window) {
        s_Window = window;
    }

    bool Input::IsKeyPressed(int key) {
        return glfwGetKey(s_Window, key) == GLFW_PRESS;
    }

    void Input::GetMousePosition(double& x, double& y) {
        glfwGetCursorPos(s_Window, &x, &y);
    }

    int Input::GetKeyPressed() {
        for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key) {
            if (glfwGetKey(s_Window, key) == GLFW_PRESS) {
                return key;
            }
        }
        return -1; // No key pressed
    }

    std::vector<int> Input::GetPressedKeys() {
        std::vector<int> pressedKeys;
        for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key) {
            if (glfwGetKey(s_Window, key) == GLFW_PRESS) {
                pressedKeys.push_back(key);
            }
        }
        return pressedKeys;
    }
}
