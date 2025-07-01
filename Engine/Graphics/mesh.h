#pragma once
#include <glad/glad.h>

namespace Engine {

    class Mesh {
    public:
        Mesh();
        ~Mesh();
        void Draw() const;

    private:
        GLuint VAO, VBO;
    };

}
