#pragma once
#include "Component.h"
#include "Transform.h"
#include "numbers"
#include "TimeManager.h"

namespace dae
{
    class GameObject;

    class RotateComponent final : public Component
    {
        float m_angle{};
        float m_speed;
        float m_radius;
    public:
        RotateComponent(GameObject* owner, float speed, float radius) :
            Component(owner), m_speed{ speed }, m_radius{ radius } {
        }
        void Update() override
        {
            constexpr float two_pi = static_cast<float>(2 * std::numbers::pi);
            m_angle += TimeManager::GetInstance().m_DeltaTime * m_speed;
            if (m_angle > two_pi)
                m_angle -= two_pi;
            GetOwner()->SetLocalPosition({
            glm::sin(m_angle) * m_radius,
            glm::cos(m_angle) * m_radius,
            0 });
        }
    };
}