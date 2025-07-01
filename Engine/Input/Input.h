#pragma once

namespace Engine {
    class Input {
    public:
        static bool IsKeyPressed(int keycode);
        static bool IsMouseButtonPressed(int button);
        static void GetMousePosition(float& x, float& y);
    };
}
