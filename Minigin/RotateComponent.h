#pragma once
#include "Component.h"
#include "Transform.h"

namespace dae
{
    class GameObject;

    class RotateComponent final : public Component
    {
    public:
        RotateComponent(GameObject* owner, float angularSpeed, GameObject* target = nullptr);
        RotateComponent(GameObject* owner, float angularSpeed, const glm::vec3& rotationCenter = glm::vec3(0.f));
        virtual ~RotateComponent() = default;


        virtual void Update() override;
        void SetRotationCenter(const glm::vec3& center) { m_RotationCenter = center; }

        void SetTarget(GameObject* target) { m_Target = target; }
        void SetAngularSpeed(float angularSpeed) { m_AngularSpeed = angularSpeed; }

    private:
        float m_AngularSpeed;             // in degrees per second
        glm::vec3 m_RotationCenter{ 0.f, 0.f, 0.f };         // used if m_Target is nullptr
        GameObject* m_Target;             // if set, its world position will be used as the center
    };
}