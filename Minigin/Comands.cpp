#include "TimeManager.h"
#include "Commands.h"

void dae::MoveCommand::Execute()
{
	dae::GameObject* owner = GetOwner();
	if (owner) owner->SetLocalPosition(owner->GetLocalPosition() + m_MoveDir * TimeManager::GetInstance().m_DeltaTime);
}