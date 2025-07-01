#include "Renderer.h"
#include "Shader.h"
#include "Mesh.h"

namespace Engine {

    void Renderer::DrawMesh(const Mesh& mesh, const Shader& shader, const glm::mat4& viewProj) {
        shader.Bind();
        shader.SetUniformMat4("u_ViewProjection", viewProj);
        mesh.Draw();
    }

}
