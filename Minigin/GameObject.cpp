#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h" 
#include "iostream"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
    std::for_each(m_components.begin(), m_components.end(), [](const auto& component) {
        component->Update();
    });
}

void dae::GameObject::LateUpdate()
{
    std::for_each(m_components.begin(), m_components.end(), [](const auto& component) {
        component->LateUpdate();
        });
}

void dae::GameObject::FixedUpdate(float fixedTimeStep)
{
    std::for_each(m_components.begin(), m_components.end(), [fixedTimeStep](const auto& component) {
        component->FixedUpdate(fixedTimeStep);
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
