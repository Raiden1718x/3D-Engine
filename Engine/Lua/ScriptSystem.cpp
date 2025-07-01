#include "../Input/Input.h"
#include <sol/sol.hpp>
#include <vector>
#include <filesystem>

namespace Engine {

    sol::state lua;

    void InitLua() {
        
        lua.open_libraries(sol::lib::base);

        lua["log"] = [](const std::string& msg) {
            std::cout << "[Lua] " << msg << "\n";
            };

        // Bind Input namespace
        lua["Input"] = lua.create_table();

        lua["Input"]["is_key_pressed"] = [](int key) {
            return Input::IsKeyPressed(key);
            };

        lua["Input"]["get_pressed_keys"] = []() {
            std::vector<int> keys = Input::GetPressedKeys();
            return keys;
            };

        lua["Input"]["get_mouse_position"] = []() {
            double x, y;
            Input::GetMousePosition(x, y);
            return std::make_tuple(x, y);
           
        };

        const std::string scriptPath = "D:/Projects/SoulsEngine/Game/Scripts/main.lua";
        if (std::filesystem::exists(scriptPath)) {
            lua.script_file(scriptPath);
        }
        else {
            std::cerr << "[Lua] Script not found: " << scriptPath << "\n";
        }

    }
    void CallLuaUpdate() {
        if (lua["update"].valid()) {
            try {
                lua["update"]();
            }
            catch (const sol::error& e) {
                std::cerr << "[Lua Error] " << e.what() << "\n";
            }
        }
	}
}
