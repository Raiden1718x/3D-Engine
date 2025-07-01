#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.h"

namespace Engine {
class Skybox {
public:
    Skybox();
    ~Skybox();
    void Draw(const Shader& shader, const glm::mat4& viewProj) const;
private:
    GLuint VAO, VBO;
};
}
