#include "Input.h"

namespace Engine {
    GLFWwindow* Input::s_Window = nullptr;
    double Input::s_LastX = 0.0;
    double Input::s_LastY = 0.0;
    bool Input::s_FirstMouse = true;

    void Input::Init(GLFWwindow* window) {
        s_Window = window;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    bool Input::IsKeyPressed(int key) {
        return glfwGetKey(s_Window, key) == GLFW_PRESS;
    }

    void Input::GetMouseDelta(double& dx, double& dy) {
        double x, y;
        glfwGetCursorPos(s_Window, &x, &y);

        if (s_FirstMouse) {
            s_LastX = x;
            s_LastY = y;
            s_FirstMouse = false;
        }

        dx = x - s_LastX;
        dy = s_LastY - y;

        s_LastX = x;
        s_LastY = y;
    }
}
