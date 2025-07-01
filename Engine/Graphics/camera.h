#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {

    class Camera {
    public:
        Camera(float fov, float aspect, float nearClip, float farClip);

        void SetPosition(const glm::vec3& pos);
        void SetRotation(float pitch, float yaw);

        void UpdateView();

        const glm::mat4& GetViewMatrix() const;
        const glm::mat4& GetProjectionMatrix() const;
        const glm::vec3& GetPosition() const;

    private:
        glm::vec3 m_Position = { 0.0f, 0.0f, 3.0f };
        float m_Pitch = 0.0f;
        float m_Yaw = -90.0f;

        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;

        void RecalculateView();
    };
}
