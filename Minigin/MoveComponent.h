#pragma once
#include <glm.hpp>
#include "Component.h"
namespace dae
{
	class MoveComponent final : public Component
	{
		float m_MaxMovementSpeed;
		glm::vec3 v;
	public:
		MoveComponent(GameObject* owner, float movementSpeed = 80.f);
		~MoveComponent() override = default;

		void Update() override;
		void UpdateDirection(glm::vec3 dir);
		MoveComponent(const MoveComponent& other) = delete;
		MoveComponent(MoveComponent&& other) noexcept = delete;
		MoveComponent& operator=(const MoveComponent& other) = delete;
		MoveComponent& operator=(MoveComponent&& other)	noexcept = delete;
	};
}