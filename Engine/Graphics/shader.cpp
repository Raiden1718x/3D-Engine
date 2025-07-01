#include "Shader.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Engine {

    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
        std::string vertexCode = LoadFile(vertexPath);
        std::string fragmentCode = LoadFile(fragmentPath);
        Compile(vertexCode, fragmentCode);
    }

    Shader::~Shader() {
        glDeleteProgram(m_ID);
    }

    void Shader::Bind() const {
        glUseProgram(m_ID);
    }

    void Shader::Unbind() const {
        glUseProgram(0);
    }

    void Shader::SetUniformMat4(const std::string& name, const glm::mat4& matrix) const {
        int loc = glGetUniformLocation(m_ID, name.c_str());
        glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]);
    }

    std::string Shader::LoadFile(const std::string& path) {
        std::ifstream in(path);
        std::stringstream ss;
        if (in) {
            ss << in.rdbuf();
            std::string sourceCode = ss.str();
            std::cout << "[Shader] Loaded: " << path << "\n" << sourceCode << "\n";
            return sourceCode;
        } else {
            std::cerr << "[Shader] Failed to load: " << path << "\n";
            return "";
        }
    }

    void Shader::Compile(const std::string& vertexSrc, const std::string& fragmentSrc) {
        unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
        const char* vSrc = vertexSrc.c_str();
        glShaderSource(vs, 1, &vSrc, nullptr);
        glCompileShader(vs);
        int success;
        char infoLog[512];
        glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vs, 512, nullptr, infoLog);
            std::cerr << "[Shader] Vertex compilation failed:\n" << infoLog << std::endl;
        }

        unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
        const char* fSrc = fragmentSrc.c_str();
        glShaderSource(fs, 1, &fSrc, nullptr);
        glCompileShader(fs);
        glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fs, 512, nullptr, infoLog);
            std::cerr << "[Shader] Fragment compilation failed:\n" << infoLog << std::endl;
        }

        m_ID = glCreateProgram();
        glAttachShader(m_ID, vs);
        glAttachShader(m_ID, fs);
        glLinkProgram(m_ID);
        glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(m_ID, 512, nullptr, infoLog);
            std::cerr << "[Shader] Program linking failed:\n" << infoLog << std::endl;
        }

        glDeleteShader(vs);
        glDeleteShader(fs);
    }

}
