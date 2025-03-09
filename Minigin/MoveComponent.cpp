#include "TimeManager.h"
#include "GameObject.h"
#include "MoveComponent.h"

dae::MoveComponent::MoveComponent(GameObject* owner, float maxMovementSpeed) :
	Component(owner),
	m_MaxMovementSpeed(maxMovementSpeed),
	v(0.0f, 0.0f, 0.0f)
{

}

void dae::MoveComponent::Update()
{
	glm::vec3 newPosition = GetOwner()->GetLocalPosition() + v * TimeManager::GetInstance().m_DeltaTime;;
	GetOwner()->SetLocalPosition(newPosition);
}

void dae::MoveComponent::UpdateDirection(glm::vec3 dir)
{
	v = dir * m_MaxMovementSpeed;
}
