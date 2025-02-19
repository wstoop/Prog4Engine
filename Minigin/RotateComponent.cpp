#include "GameObject.h"
#include "Transform.h"
#include "TimeManager.h"
#include "iostream"
#include "RotateComponent.h"

namespace dae {

    RotateComponent::RotateComponent(GameObject* owner, float angularSpeed, const glm::vec3& rotationCenter)
        : Component(owner)
        , m_AngularSpeed(angularSpeed)
        , m_RotationCenter(rotationCenter)
        , m_Target(nullptr)
    {
    }

    RotateComponent::RotateComponent(GameObject* owner, float angularSpeed, GameObject* target)
        : Component(owner)
        , m_AngularSpeed(angularSpeed)
        , m_Target(target)
    {
    }

    void RotateComponent::Update()
    {

        // Determine the rotation center: use the target's world position if provided, otherwise the static center.
        glm::vec3 center = (m_Target != nullptr) ? m_Target->GetWorldPosition() : m_RotationCenter;

        // Get the owner's current world position.
        glm::vec3 currentPos = Component::GetOwner()->GetWorldPosition();

        // Calculate the offset from the center to the current position.
        glm::vec3 offset = currentPos - center;

        // Calculate the rotation angle in radians.
        float angleRadians = glm::radians(m_AngularSpeed * TimeManager::GetInstance().GetDeltaTime());

        // Compute the cosine and sine of the angle.
        float cosAngle = std::cos(angleRadians);
        float sinAngle = std::sin(angleRadians);

        // Rotate the offset around the Z-axis (assuming rotation in the X-Y plane).
        glm::vec3 rotatedOffset;
        rotatedOffset.x = offset.x * cosAngle - offset.y * sinAngle;
        rotatedOffset.y = offset.x * sinAngle + offset.y * cosAngle;
        rotatedOffset.z = offset.z; // Leave Z unchanged

        // Compute the new world position.
        glm::vec3 newWorldPos = center + rotatedOffset;

        // Update the owner's position.
        // If the owner has a parent, convert the computed world position
        // to the owner's local coordinates by subtracting the parent's world position.
        auto owner = Component::GetOwner();
        if (Component::GetOwner()->GetParent() != nullptr)
        {
            newWorldPos -= owner->GetParent()->GetWorldPosition();
        }
        owner->SetLocalPosition(newWorldPos);
    }

}