#include <string>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h" 
#include "iostream"
#include "GameObject.h"

dae::GameObject::~GameObject()
{
	m_IsDestroyed = true;
}

void dae::GameObject::Update()
{
    std::for_each(m_components.begin(), m_components.end(), [](const auto& component) {
        component->Update();
    });
}

void dae::GameObject::LateUpdate()
{
	if (m_IsDestroyed)
	{
        m_components.clear();
        m_children.clear();
        if (m_parent) m_parent->RemoveChild(this);
        return;
	}

    std::for_each(m_components.begin(), m_components.end(), [](const auto& component) {
        component->LateUpdate();
        });
}

void dae::GameObject::FixedUpdate()
{
    std::for_each(m_components.begin(), m_components.end(), [](const auto& component) {
        component->FixedUpdate();
        });
}

void dae::GameObject::Render() const
{
    std::for_each(m_components.begin(), m_components.end(), [](const auto& component) {
        component->Render();
        });
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
    if (IsChild(parent) || parent == this || m_parent == parent)
        return;
    if (parent == nullptr)
        SetLocalPosition(GetWorldPosition());
    else
    {
        if (keepWorldPosition)
            SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
        SetPositionDirty();
    }
    if (m_parent) m_parent->RemoveChild(this);
    m_parent = parent;
    if (m_parent) m_parent->AddChild(this);
}
void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
    m_localPosition = pos;
    SetPositionDirty();
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
    if (m_positionIsDirty)
        UpdateWorldPosition();
    return m_worldPosition;
}
void dae::GameObject::UpdateWorldPosition()
{
    if (m_positionIsDirty)
    {
        if (m_parent == nullptr)
            m_worldPosition = m_localPosition;
        else
            m_worldPosition = m_parent->GetWorldPosition() + m_localPosition;
    }
    m_positionIsDirty = false;
}

void dae::GameObject::AddChild(GameObject* child)
{
    m_children.push_back(child);
}

void dae::GameObject::RemoveChild(GameObject* child)
{
    m_children.erase(std::remove_if(m_children.begin(), m_children.end(), 
        [child](const GameObject* ptr) { return ptr == child; }), m_children.end());
}

bool dae::GameObject::IsChild(GameObject* child) const
{
    return std::find_if(m_children.begin(), m_children.end(), 
        [child](const GameObject* ptr) { return ptr == child; }) != m_children.end();
}

void dae::GameObject::SetPositionDirty()
{
    m_positionIsDirty = true;
    for (auto child : m_children)
        child->SetPositionDirty();
}

dae::GameObject * dae::GameObject::GetParent()
{
	return m_parent;
}

const glm::vec3& dae::GameObject::GetLocalPosition()
{
    return m_localPosition;
}


