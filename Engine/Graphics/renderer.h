#pragma once
#include <glm/glm.hpp>

namespace Engine {
    class Shader;
    class Mesh;

    class Renderer {
    public:
        void DrawMesh(const Mesh& mesh, const Shader& shader, const glm::mat4& viewProj);
    };
}
