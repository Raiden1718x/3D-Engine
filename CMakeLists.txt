cmake_minimum_required(VERSION 3.16)
project(SoulsEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------
# Include directories
# -------------------------
include_directories(
    Engine/Core
    Engine/Graphics
    Engine/ECS
    Engine/Lua
    Engine/Assets

    ThirdParty/glad/include
    ThirdParty/glm
    ThirdParty/glfw/include
    ThirdParty/sol2/include
    ThirdParty/bullet3/src
    ThirdParty/lua/include
    ThirdParty/imgui
)

# -------------------------
# Link directories (for precompiled libs)
# -------------------------
link_directories(
    ThirdParty/lua/lib
)

# -------------------------
# External Libraries
# -------------------------

# GLFW
add_subdirectory(ThirdParty/glfw)

# GLAD
add_library(glad STATIC
    ThirdParty/glad/src/glad.c
 "Engine/Lua/ScriptSystem.h" "Engine/Lua/ScriptSystem.cpp" "Engine/Input/Input.cpp" "Engine/Input/Input.h" "Engine/Graphics/camera.h" "Engine/Graphics/camera.cpp")
target_include_directories(glad PUBLIC ThirdParty/glad/include)

# Bullet
add_subdirectory(ThirdParty/bullet3)


# -------------------------
# Source Files
# -------------------------
file(GLOB_RECURSE ENGINE_SRC
    Engine/Core/*.cpp
    Engine/Graphics/*.cpp
    Engine/ECS/*.cpp
    Engine/Lua/*.cpp
    Engine/Assets/*.cpp
)



# -------------------------
# Executable
# -------------------------
add_executable(SoulsEngine
    main.cpp
    ${ENGINE_SRC}
    Engine/Graphics/Skybox.cpp
    "Engine/Lua/ScriptSystem.h" "Engine/Lua/ScriptSystem.cpp" "Engine/Input/Input.cpp" "Engine/Input/Input.h" "Engine/Graphics/camera.h" "Engine/Graphics/camera.cpp")

# -------------------------
# Link Libraries
# -------------------------
target_link_libraries(SoulsEngine
    glfw
    glad
    BulletDynamics
    BulletCollision
    LinearMath
    lua54
)

# ImGui
file(GLOB IMGUI_SRC
    ThirdParty/imgui/*.cpp
    ThirdParty/imgui/backends/imgui_impl_glfw.cpp
    ThirdParty/imgui/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SRC} "Engine/Graphics/camera.h" "Engine/Graphics/camera.cpp")

target_include_directories(imgui PUBLIC
    ThirdParty/imgui
    ThirdParty/imgui/backends
)

target_link_libraries(SoulsEngine imgui)

file(COPY Game/Shaders DESTINATION ${CMAKE_BINARY_DIR}/Game)


# -------------------------
# Platform-specific settings
# -------------------------
if (WIN32)
    target_link_libraries(SoulsEngine opengl32)

    # Auto-copy lua54.dll to the output directory
    add_custom_command(TARGET SoulsEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/ThirdParty/lua/bin/lua54.dll
            $<TARGET_FILE_DIR:SoulsEngine>
    )
endif()
