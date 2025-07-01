#include "Camera.h"

namespace Engine {

    Camera::Camera(float fov, float aspect, float nearClip, float farClip) {
        m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspect, nearClip, farClip);
        RecalculateView();
    }

    void Camera::SetPosition(const glm::vec3& pos) {
        m_Position = pos;
        RecalculateView();
    }

    void Camera::SetRotation(float pitch, float yaw) {
        m_Pitch = pitch;
        m_Yaw = yaw;
        RecalculateView();
    }

    void Camera::RecalculateView() {
        glm::vec3 direction;
        direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        direction.y = sin(glm::radians(m_Pitch));
        direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

        glm::vec3 front = glm::normalize(direction);
        glm::vec3 right = glm::normalize(glm::cross(front, { 0.0f, 1.0f, 0.0f }));
        glm::vec3 up = glm::cross(right, front);

        m_ViewMatrix = glm::lookAt(m_Position, m_Position + front, up);
    }

    void Camera::UpdateView() {
        RecalculateView();
    }

    const glm::mat4& Camera::GetViewMatrix() const { return m_ViewMatrix; }
    const glm::mat4& Camera::GetProjectionMatrix() const { return m_ProjectionMatrix; }
    const glm::vec3& Camera::GetPosition() const { return m_Position; }

}
