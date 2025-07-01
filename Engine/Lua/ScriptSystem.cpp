#include "ScriptSystem.h"
#include <sol/sol.hpp>
#include <iostream>

namespace Engine {
    void InitLua() {
        sol::state lua;
        lua.open_libraries(sol::lib::base);

        lua["log"] = [](const std::string& msg) {
            std::cout << "[Lua] " << msg << "\n";
            };

        lua.script(R"(
            log("Hello from Lua!")
        )");
    }
}
