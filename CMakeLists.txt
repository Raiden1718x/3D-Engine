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
    ThirdParty/sol2/include
    ThirdParty/bullet3/src
    ThirdParty/lua/include
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
 "Engine/Lua/ScriptSystem.h" "Engine/Lua/ScriptSystem.cpp")
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
 "Engine/Lua/ScriptSystem.h" "Engine/Lua/ScriptSystem.cpp")

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
