#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Engine {

    class Shader {
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        // Optional: uniforms
        void SetUniformMat4(const std::string& name, const glm::mat4& matrix) const;

    private:
        unsigned int m_ID;

        std::string LoadFile(const std::string& path);
        void Compile(const std::string& vertexSrc, const std::string& fragmentSrc);
    };

}
